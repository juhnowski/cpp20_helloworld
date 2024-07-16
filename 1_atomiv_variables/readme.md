# Модель памяти
## mutex
- test_spinlock.cpp - циклическая блокировка

- test_spinLockSleep.cpp - сравнение циклической блокировки с мьютексом mutex.cpp
нагрузка - spinLockSleep.png, видно что нагрузка сильно подскакивает, а в mutex.exe вообще не видно нагрузки

## Синхронизация потоков на основе типа std::atomic_flag
- threadSynchronisationAtomicFlag.cpp

## Использование переменных условия
std::atomic<bool>
- conditionVariable.cpp

- Реализация переменной условия на основе типа std::atomic<bool>
atomicCondition.cpp

# Цикл ожидания на основе семантики захвата освобождения
- spinlockAckuireRelease.cpp

# ослабленная семантика
- relaxed.cpp








