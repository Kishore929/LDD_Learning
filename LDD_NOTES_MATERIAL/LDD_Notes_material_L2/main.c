

void KM_LCD_Init(void);

void HD44780_Str_XY(char , char , char *);

int main()
{
 
	KM_LCD_Init();

        HD44780_Str_XY(1, 1, "KERNEL");

	return 0;
}
