# LanQiao-LCD
#LanqiaoCup
#1.两种取反方式区别
（1）逻辑非
view=!view
结果只能有两种,并且类型不变，（int仍然是int）
0->1->0->1
（2）按位取反
view=~view
即对view每个二进制位取反
// 寄存器位操作（如GPIO状态翻转）
uint32_t reg = 0xF0;
reg = ~reg;  // 0xF0 → 0x0F
操作场景：
#define LED_MASK (1 << 3)  // 第3位控制LED
uint8_t port = 0xFF;
port &= ~LED_MASK;  // 清除第3位（其他位保留）
#2.LCD多层显示封装
（1）v2.1
if(view==0)
	{
		const char* displayTexts[]={
			"       Data",
			" ",
			"   CNBR:2",
			"   VNBR:4",
			"   IDLE:2"
		};
		uint8_t num=sizeof(displayTexts)/sizeof(char*);
		for(uint8_t i=0;i<num;i++)
	{
		LCD_DisplayStringLine(24+i*24, (unsigned char *)displayTexts[i]);
	}
 （2）v2.2动态刷新
 typedef struct {
    uint8_t line;
    char prefix[20];
    void* data;
    char format[10];
} DisplayItem;

void refreshDisplay(DisplayItem* items, uint8_t count) {
    char buffer[30];
    for(uint8_t i = 0; i < count; i++) {
        if(strcmp(items[i].format, "%f") == 0) {
            sprintf(buffer, "%s%.2f", items[i].prefix, *(float*)items[i].data);
        }
        else {
            sprintf(buffer, "%s%d", items[i].prefix, *(int*)items[i].data);
        }
        LCD_DisplayStringLine(items[i].line, (uint8_t*)buffer);
    }
}

// 使用示例
if(view == 0) {
    int counter = 2;
    float voltage = 3.3f;
    
    DisplayItem items[] = {
        {Line4, "   CNBR:", &counter, "%d"},
        {Line5, "  Voltage:", &voltage, "%f"}
    };
    
    refreshDisplay(items, sizeof(items)/sizeof(DisplayItem));
}
#3.解决清屏闪烁
闪烁原因：
清屏操作本质是向整个帧缓冲区写入背景色
LCD控制器逐行刷新需要时间（典型50-100ms）
人眼视觉暂留时间约100ms，导致感知到闪烁

