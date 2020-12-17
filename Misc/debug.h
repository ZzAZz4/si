#ifndef SI_DEBUG_H
#define SI_DEBUG_H

#ifndef NDEBUG
#define EXPECTS(condition, msg) \
if (!(condition)) \
{ \
    fprintf(stderr, "At line %d of %s\n", __LINE__, __FILE__);\
    fprintf(stderr, "On call to %s\n", __PRETTY_FUNCTION__);\
    throw std::logic_error(msg " (failed " #condition ")");\
}


#define EXPECTSVAL(val_1, target) \
if (!((val_1) == (target))) \
{ \
    fprintf(stderr, "At line %d of %s\n", __LINE__, __FILE__);\
    fprintf(stderr, "On call to %s\n", __PRETTY_FUNCTION__);\
    fprintf(stderr, "Expected: %d, got %d\n", (val_1), (target));\
    throw std::logic_error("Equality failed: " #val_1 " == " #target ")");\
}

#else
#define EXPECTS(...)
#endif

#endif //SI_DEBUG_H
