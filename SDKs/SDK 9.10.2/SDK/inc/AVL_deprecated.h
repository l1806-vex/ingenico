/*En GNU, on g�re la commande deprecated */
/*En ARM, on g�re avec un define */
#if defined(__GNUC__)
#define AVL_DEPRECATED __attribute__ ((deprecated))
#else
#define AVL_DEPRECATED
#endif

