/*En GNU, on gère la commande deprecated */
/*En ARM, on gère avec un define */
#if defined(__GNUC__)
#define AVL_DEPRECATED __attribute__ ((deprecated))
#else
#define AVL_DEPRECATED
#endif

