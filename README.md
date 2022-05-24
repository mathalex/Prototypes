# Prototypes
Функции протестированы в файле `test.cpp` с сопутствующими комментариями (запуск с помощью любого компилятора C++, например, gcc; основные флаги: `-std=c++20 -O2`, но, вероятно, более низкая версия и отсутсвие оптимизации ни на что не повлияют). Стоит отметить, что реализованные предсказания лучше всего себя демонстрируют на равномерной по времени выборке (то есть все наблюдения идут через одинаковые промежутки времени). Тем не менее, неравномерный подход также поддерживается в данной реализации.

***Реализованы (зачёркнутые сегодня будут доделаны) следующие объекты:***

* Абстрактный класс Forecast, объединяющий все виды предсказания (тут все smoothing)

* Simple moving average

* Simple exponential smoothing

* Double exponential smoothing

* ~~Triple exponential smoothing (Holt Winters)~~

* ~~Функция, принимающая массив, вид предсказания (Forecast) и степень зависимости от прошлого: опредеяет точки "разладки" с помощью стандартных отклонений~~

* ~~Функция, заполняющая отсутвующие данные в массиве предсказанием (принимает объект Forecast)~~ 
