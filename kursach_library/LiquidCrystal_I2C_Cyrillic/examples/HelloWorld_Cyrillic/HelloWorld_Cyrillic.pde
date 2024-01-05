//Compatible with the Arduino IDE 1.0
//Library version:1.0

#include <LiquidCrystal_I2C_Cyrillic.h>

// Объект класса LiquidCrystal_I2C_Cyrillic для дисплея
// Первый параметр - i2c адрес дисплея
// Второй параметр - количество символов в строке
// Третий параметр - количество строк
// Класс LiquidCrystal_I2C_Cyrillic полностью дублирует
// по функционалу класс LiquidCrystal_I2C (наследует его),
// добавляя метод printCyrillic(const char* str, int x, int y)
// для вывода текста, содержащего кирилицу
LiquidCrystal_I2C_Cyrillic lcd(0x3F, 16, 2);


void setup()
{
  lcd.init();
  lcd.backlight(); // Включаем подсветку дисплея
  // Выводим "Привет, Мир!"
  // Символы, начертания которых не имеют аналогов в латинице, заменяем
  // на коды (см. ниже)
  // Одновременно на диспелее могут отображаться до 8-ми различных
  // символов, которые не имеют аналога в латинице
  lcd.printCyrillic("\x088" "p" "\x098" "\x093" "e" "\x09F" ", М" "\x098" "p!",0,0);
}

void loop()
{
}

/* Коды символов
Б \x080
Г \x081
Ё \x082
Ж \x083
З \x084
И \x085
Й \x086
Л \x087
П \x088
У \x089
Ф \x08A 
Ч \x08B
Ш \x08C
Ъ \x08D
Ы \x08E
Э \x08F
Ю \x090
Я \x091
б \x092
в \x093
г \x094
ё \x095
ж \x096
з \x097
и \x098
й \x099
к \x09A
л \x09B
м \x09C
н \x09D
п \x09E
т \x09F
ч \x0A0
ш \0xA1
ъ \x0A2
ы \x0A3
ь \x0A4
э \x0A5
ю \x0A6
я \x0A7
Д \x0A8
Ц \x0A9
Щ \x0AA
д \x0AB
ф \x0AC
ц \x0AD
щ \x0AE
*/