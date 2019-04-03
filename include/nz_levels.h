#ifndef NZ_LEVELS_H
#define NZ_LEVELS_H

// This file contains error levels description

#ifndef NZ_SPACE_H
#error "ERROR! This file should never be included whitout space definition!"
#endif


#ifdef NZ_KERNELSPACE

#define NZ_LVL_EMERG    KERN_EMERG
#define NZ_LVL_ALERT    KERN_ALERT
#define NZ_LVL_CRIT     KERN_CRIT
#define NZ_LVL_ERR      KERN_ERR
#define NZ_LVL_WARNING  KERN_WARNING
#define NZ_LVL_NOTICE   KERN_NOTICE
#define NZ_LVL_INFO     KERN_INFO
#define NZ_LVL_DEBUG    KERN_DEBUG
#define NZ_LVL_DEFAULT  KERN_DEFAULT

#else

#define NZ_LVL_EMERG    "[NZ_EMERG  ]"
#define NZ_LVL_ALERT    "[NZ_ALERT  ]"
#define NZ_LVL_CRIT     "[NZ_CRIT   ]"
#define NZ_LVL_ERR      "[NZ_ERROR  ]"
#define NZ_LVL_WARNING  "[NZ_WARNING]"
#define NZ_LVL_NOTICE   "[NZ_NOTICE ]"
#define NZ_LVL_INFO     "[NZ_INFO   ]"
#define NZ_LVL_DEBUG    "[NZ_DEBUG  ]"
#define NZ_LVL_DEFAULT  "[NZ_DEFAULT]"

#endif



#endif // NZ_LEVELS_H
