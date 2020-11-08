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
#else
#define EXPECTS(...)
#endif

#endif //SI_DEBUG_H
