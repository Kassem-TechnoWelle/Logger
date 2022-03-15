#include <iostream>
#include <string>
#include <stdint.h>
#include <time.h>

#define maxNumOfLoggers 1000
#define PERSISTENT_LVL_MAX 3
#define PERSISTENT_LVL_MIN 0
#define PRIORITY_LVL_MAX 3
#define PRIORITY_LVL_MIN 0
#define SET 1
#define CLEAR 0

typedef uint16_t loggerID;
typedef uint8_t loggerIDFlag;
typedef uint8_t loggerReturnType;
typedef uint8_t loggerMsgPersistency;
typedef uint8_t loggerMsgPriority;
typedef std::string loggerText;
typedef std::string  loggerTimeStamp;

uint16_t loggerIDIdx[maxNumOfLoggers] = {0};

class logger{
public:

    loggerReturnType createNewLogger(loggerMsgPersistency lvl, loggerMsgPriority priority);
    loggerReturnType logNewMsg(loggerText msg);
    loggerText logGetMsg(void);
    loggerReturnType logClear(void);
    loggerReturnType logDelete(void);
private:
    loggerID id;
    loggerText txt;
    loggerTimeStamp timeStamp;
    loggerMsgPersistency persistentLvl;
    loggerMsgPriority priorityLvl;
    loggerReturnType logSetID(void);
    loggerReturnType logClearID(void);


};

loggerReturnType logger::createNewLogger(loggerMsgPersistency lvl, loggerMsgPriority priority) {
    loggerReturnType output = CLEAR;
    if(PERSISTENT_LVL_MIN<lvl<PERSISTENT_LVL_MAX && PRIORITY_LVL_MIN<priority<PRIORITY_LVL_MAX){
        if(logSetID()){
            persistentLvl = lvl;
            priorityLvl = priority;
            output = SET;
        }
    }
    return output;
}
loggerReturnType logger::logNewMsg(loggerText msg) {
    txt.append(msg);
    txt.append(" timeStamp \n");
}
loggerReturnType logger::logClear(){
    txt = "";
}
loggerReturnType logger::logDelete() {
    logClearID();
}
loggerReturnType logger::logSetID() {
    uint8_t loopIdx;
    loggerReturnType output = CLEAR;
    for(loopIdx = CLEAR;loopIdx<maxNumOfLoggers;loopIdx++){
        if(loggerIDIdx[loopIdx] == CLEAR){
            id = loopIdx;
            loggerIDIdx[loopIdx] = SET;
            output = SET;
            break;
        }
    }
    return output;
}
loggerReturnType logger::logClearID() {
    loggerReturnType output = CLEAR;
    if(CLEAR<=id<maxNumOfLoggers){
        loggerIDIdx[id] = CLEAR;
        output = SET;
    }
    return output;
}

loggerText logger::logGetMsg() {
    return txt;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    logger myLogger;
    myLogger.createNewLogger(2,2);
    myLogger.logNewMsg("Logger Msg");
    myLogger.logNewMsg("Hello Logger");
    std::cout << myLogger.logGetMsg() << std::endl;
    std::cout << loggerIDIdx[500] << std::endl;
    return 0;
}
