
#ifdef DEBUG
#define LOG(x) Serial.print(x);
#define LOGLN(x) Serial.println(x);
#define LOGF(...) Serial.printf(__VA_ARGS__);
#else
#define LOG(x) x;
#define LOGLN(x) x;
#define LOGF(...) __VA_ARGS__;
#endif
