#ifndef HEADER_H
#define HEADER_H

#include <bits/stdc++.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>

unsigned mode = S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH;
const char *CommonFile = "pipe";
const char *SemaphoreName = "semaphore";

using namespace std;

#endif