int convert(char* date) {
    int days[] = {31, 28, 31, 30, 31, 30,
                  31, 31, 30, 31, 30, 31};

    int m, d;
    sscanf(date, "%d-%d", &m, &d);

    for (int i = 0; i < m - 1; i++) {
        d += days[i];
    }

    return d;
}

int countDaysTogether(char* arriveAlice, char* leaveAlice, char* arriveBob, char* leaveBob) {
    int a1 = convert(arriveAlice);
    int a2 = convert(leaveAlice);
    int b1 = convert(arriveBob);
    int b2 = convert(leaveBob);

    int start = a1 > b1 ? a1 : b1;
    int end = a2 < b2 ? a2 : b2;

    int result = end - start + 1;

    return result > 0 ? result : 0;
}