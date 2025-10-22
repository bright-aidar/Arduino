// Подключаем библиотеку DHT
#include <DHT.h>

// Определяем пин и тип датчика
#define DHT_PIN 2
#define DHT_TYPE DHT11
// Назначаем пин на транзистор 2n2222A
int npn = 3;
// Создаем объект датчика
DHT dht(DHT_PIN, DHT_TYPE);


void setup(){
  // Добавление пина транзистора
  pinMode (npn, OUTPUT);

  // Инициализация последовательного порта
  Serial.begin(9600);
  Serial.println("DHT11 тестовый запуск");

  // Инициализация датчика
  dht.begin();

  // Ждём 2 секунды для стабтлтзацтт датчика
  delay(2000);
}

void loop(){
  // Ждем мужду измерениями (минимум 2 секунды для DHT11)
  delay(2000);

  // Читаем температуру и влажность
  float humidity = dht.readHumidity();  // Влажность в %
  float temperature = dht.readTemperature(); // Температура в °C
  
  // Проверяем, удалось ли прочитать данные
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Ошибка чтения DHT11!");
    return;
  }



  // Выводим данные в монитор порта
  Serial.print("Влажность: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Температура: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Можно также рассчитать индекс тепла (ощущаемую температуру)
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
  Serial.print("Индекс тепла: ");
  Serial.print(heatIndex);
  Serial.println("°C");

  Serial.println("------------------------");
  
    // Проверка транзистора
  digitalWrite (npn, HIGH);
  delay(1000);
  digitalWrite (npn, LOW);
  delay(1000);
}
