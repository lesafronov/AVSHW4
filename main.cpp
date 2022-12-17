#include <pthread.h>
#include <semaphore.h>
#include <conio.h>
#include <string>
#include <vector>
#include "iostream"

using std::string;

pthread_mutex_t mutex; //mutex...
sem_t semaphore;
static int M_counter = 0;
static int N_counter = 0;
static int K_counter = 0;
static int M, N, K;
string arr[20][20][20];
/**
 * Ввод параметров библиотеки
 */
void parse_input() {
    char input[1000];
    printf("%s", "Enter number of rows:\n");
    do {
        scanf("%s", input);
        M = atoi(input);
        if (M <= 1 || M >= 21) {
            printf("%s", "Incorrect input,enter 1 < number < 21\n");
        }
    } while (M <= 1 || M >= 21);
    printf("%s", "Enter number of cupboards in a row:\n");
    do {
        scanf("%s", input);
        N = atoi(input);
        if (N <= 1 || N >= 21) {
            printf("%s", "Incorrect input,enter 1 < number < 21\n");
        }
    } while (N <= 1 || N >= 21);
    printf("%s", "Enter number of books in a cupboard:\n");
    do {
        scanf("%s", input);
        K = atoi(input);
        if (K <= 1 || K >= 21) {
            printf("%s", "Incorrect input,enter 1 < number < 21\n");
        }
    } while (K <= 1 || K >= 21);
}

void inventory_completed() {
    for (int i = 0; i < M; ++i) {
        std::cout << "Row with number:" << " " << i + 1 << "\n";
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < K; ++k) {
                std::cout << arr[i][j][k];
                for (int l = 0; l < 10 - arr[i][j][k].length(); ++l) {
                    std::cout << " ";
                }
            }
            std::cout << "\n";
        }
    }
}
/**
 * Когда счетчики достигают заданных значений программа выводит библиотеку в консоль
 */
void raise_counters() {
    K_counter++;
    if (K_counter == K) {
        N_counter++;
        K_counter = 0;
    }
    if (N_counter == N) {
        M_counter++;
        N_counter = 0;
    }
    if (M_counter == M) {
        std::cout << "Inventory completed..." << "\n";
        inventory_completed();
    }
}
/**
 * Метод ввода рандомных названий книг
 * @param pVoid
 * @return
 */
void *random_input(void *pVoid) {
    char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int random_letter = rand() % 26;
    int random_length = rand() % 10;
    arr[M_counter][N_counter][K_counter] = "";
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < random_length; ++i) {
        srand((unsigned) time(nullptr));
        arr[M_counter][N_counter][K_counter] += alphabet[random_letter];
        random_letter = rand() % 26;
    }
    raise_counters();
    pthread_mutex_unlock(&mutex);
    return nullptr;
}

/**
 * Ввод с консоли
 * @return
 */
void *input_from_console() {
    string input;
    pthread_mutex_lock(&mutex);
    std::cout << "Enter name of the book with number " << K_counter + 1 << ":";
    std::cin >> input;
    while (input.length() < 1 || input.length() > 10) {
        std::cout << "\nIncorrect name. Please enter name with length bigger then 0 and smaller then 11:";
        std::cin >> input;
    }
    arr[M_counter][N_counter][K_counter] = input;
    raise_counters();
    pthread_mutex_unlock(&mutex);
    return nullptr;
}
/**
 * Выбор ввода рандомного либо консоль
 * @return
 */
int console_or_random() {
    string input;
    std::cout << "If you want console input enter 1. If you want random input enter 2: \n";
    std::cin >> input;
    while (input != "1" && input != "2") {
        std::cout << "Incorrect input. Enter 1 or 2: \n";
        std::cin >> input;
    }
    return stoi(input);

}

int main() {
    parse_input();
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread[M * N * K];
    int random_or_console = console_or_random();
    if (random_or_console == 1) {
        for (int i = 0; i < M * N * K; ++i) {
            input_from_console();
        }
    } else {
        for (int i = 0; i < M * N * K; ++i) {
            pthread_create(&thread[i], NULL, random_input, NULL);
        }
    }
    getch();
    return 0;
}
