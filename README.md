# AVSHW4
4 Парадигма параллельного программирования взаимодействующие равные(Портфель задач)
Взаимодействующие равные – модель, в которой исключен не занимающийся непосредственными вычислениями управляющий поток.

Распределение работ в таком приложении либо фиксировано заранее, либо динамически определяется во время выполнения. 
Одним из распространенных способов динамического распределения работ является «портфель задач». 
Портфель задач, как правило, реализуется с помощью разделяемой переменной, доступ к которой в один момент времени имеет только один процесс.
Вычислительная задача делится на конечное число подзадач. 
Как правило, каждая подзадача должна выполнить однотипные действия над разными данными. 
Подзадачи нумеруются, и каждому номеру определяется функция, которая однозначно отражает номер задачи на соответствующий ему набор данных. 
Создается переменная, которую следует выполнять следующей. 
Каждый поток сначала обращается к портфелю задач для выяснения текущего номера задачи, после этого увеличивает его, потом берет соответствующие данные и выполняет задачу, затем обращается к портфелю задач для выяснения следующего номера задачи.
Естественно должен быть предусмотрен механизм остановки процессов при исчерпывании всего множества задач, как в «производителях и потребителях».
То есть поток получает задачу из портфеля и пока задача остается не выполненной, поток ее решает, а затем снова получает задачу из портфеля.
Рассмотрим задачу вычисления произведения матриц. 
Подзадачей будет вычисление строк результирующей матрицы, а портфель задач – переменная, в которую будем считать строки. 
При получении задачи, происходит считывание значения счетчика и его увеличение на 1.
Когда счетчик будет равен размерности матрицы, вычисления заканчиваются. 
То есть поток без прерывания остальных возьмет задачу, при этом выполнив увеличение счетчика.
Таким образом, процессы работают независимо, каждый со своей скоростью, синхронизация происходит с помощью портфеля задач.
Проблема реализации этого алгоритма в том, что доступ к портфелю задач должен быть безопасным. 
Если между взятием новой задачи и увеличением счетчика работа выполняющего их потока прервется, то некоторую задачу, возможно, отработают несколько потоков.
