// Пин для подключения термистора
const int thermistorPin = A0;

// Параметры термистора (стандартные для 10кОм термистора)
const int nominalResistance = 10000;  // 10 кОм при 25°C
const int nominalTemp = 25;           // 25°C
const int bCoefficient = 3950;        // Бета-коэффициент
const int seriesResistor = 10000;     // Сопротивление резистора - 10 кОм

// Функция для чтения температуры
float readTemperature() {
  // Читаем сырое значение с аналогового пина
  int rawValue = analogRead(thermistorPin);
  
  // Рассчитываем сопротивление термистора
  float resistance = (1023.0 / rawValue - 1.0) * seriesResistor;
  
  // Рассчитываем температуру по формуле Стейнхарта-Харта
  float temp;
  temp = resistance / nominalResistance;     // R/R0
  temp = log(temp);                          // ln(R/R0)
  temp /= bCoefficient;                      // 1/B * ln(R/R0)
  temp += 1.0 / (nominalTemp + 273.15);     // + 1/T0
  temp = 1.0 / temp;                         // Инвертируем
  temp -= 273.15;                            // В Цельсии
  
  return temp;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Начинаем чтение температуры...");
}

void loop() {
  // Читаем температуру
  float temperature = readTemperature();
  
  // Выводим в Serial Monitor
  Serial.print("Температура: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  delay(1000); // Ждем 1 секунду
}
