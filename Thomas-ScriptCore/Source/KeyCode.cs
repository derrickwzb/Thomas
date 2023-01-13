using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Thomas
{
    public enum KeyCode
    {
        TH_KEY_SPACE       =       32,
        TH_KEY_APOSTROPHE  =       39,  /* ' */
        TH_KEY_COMMA       =       44,  /* , */
        TH_KEY_MINUS       =       45,  /* - */
        TH_KEY_PERIOD      =       46,  /* . */
        TH_KEY_SLASH              =47,  /* / */
        TH_KEY_0                  =48,
        TH_KEY_1                  =49,
        TH_KEY_2                  =50,
        TH_KEY_3                  =51,
        TH_KEY_4                  =52,
        TH_KEY_5                  =53,
        TH_KEY_6                  =54,
        TH_KEY_7                  =55,
        TH_KEY_8                  =56,
        TH_KEY_9                  =57,
        TH_KEY_SEMICOLON          =59,  /* ; */
        TH_KEY_EQUAL              =61,  /* = */
        TH_KEY_A                  =65,
        TH_KEY_B                  =66,
        TH_KEY_C                  =67,
        TH_KEY_D                  =68,
        TH_KEY_E                  =69,
        TH_KEY_F                  =70,
        TH_KEY_G                  =71,
        TH_KEY_H                  =72,
        TH_KEY_I                  =73,
        TH_KEY_J                  =74,
        TH_KEY_K                  =75,
        TH_KEY_L                  =76,
        TH_KEY_M                  =77,
        TH_KEY_N                  =78,
        TH_KEY_O                  =79,
        TH_KEY_P                  =80,
        TH_KEY_Q                  =81,
        TH_KEY_R                  =82,
        TH_KEY_S                  =83,
        TH_KEY_T                  =84,
        TH_KEY_U                  =85,
        TH_KEY_V                  =86,
        TH_KEY_W                  =87,
        TH_KEY_X                  =88,
        TH_KEY_Y                  =89,
        TH_KEY_Z                  =90,
        TH_KEY_LEFT_BRACKET       =91,  /* [ */
        TH_KEY_BACKSLASH          =92, /* \ */
        TH_KEY_RIGHT_BRACKET      =93,  /* ] */
        TH_KEY_GRAVE_ACCENT       =96,  /* ` */
        TH_KEY_WORLD_1            =161, /* non-US #1 */
        TH_KEY_WORLD_2            =162, /* non-US #2 */

        /* Function keys */
        TH_KEY_ESCAPE             =256,
        TH_KEY_ENTER              =257,
        TH_KEY_TAB                =258,
        TH_KEY_BACKSPACE          =259,
        TH_KEY_INSERT             =260,
        TH_KEY_DELETE             =261,
        TH_KEY_RIGHT              =262,
        TH_KEY_LEFT               =263,
        TH_KEY_DOWN               =264,
        TH_KEY_UP                 =265,
        TH_KEY_PAGE_UP            =266,
        TH_KEY_PAGE_DOWN          =267,
        TH_KEY_HOME               =268,
        TH_KEY_END                =269,
        TH_KEY_CAPS_LOCK         = 280,
        TH_KEY_SCROLL_LOCK       = 281,
        TH_KEY_NUM_LOCK          = 282,
        TH_KEY_PRINT_SCREEN      = 283,
        TH_KEY_PAUSE             = 284,
        TH_KEY_F1                = 290,
        TH_KEY_F2                = 291,
        TH_KEY_F3                = 292,
        TH_KEY_F4                = 293,
        TH_KEY_F5                = 294,
        TH_KEY_F6                = 295,
        TH_KEY_F7                = 296,
        TH_KEY_F8                = 297,
        TH_KEY_F9                = 298,
        TH_KEY_F10               = 299,
        TH_KEY_F11              =  300,
        TH_KEY_F12               = 301,
        TH_KEY_F13               = 302,
        TH_KEY_F14               = 303,
        TH_KEY_F15              =  304,
        TH_KEY_F16              =  305,
        TH_KEY_F17              =  306,
        TH_KEY_F18              =  307,
        TH_KEY_F19              =  308,
        TH_KEY_F20              =  309,
        TH_KEY_F21              =  310,
        TH_KEY_F22               = 311,
        TH_KEY_F23              =  312,
        TH_KEY_F24               = 313,
        TH_KEY_F25              =  314,
        TH_KEY_KP_0             =  320,
        TH_KEY_KP_1             =  321,
        TH_KEY_KP_2             =  322,
        TH_KEY_KP_3              = 323,
        TH_KEY_KP_4              = 324,
        TH_KEY_KP_5              = 325,
        TH_KEY_KP_6             =  326,
        TH_KEY_KP_7              = 327,
        TH_KEY_KP_8              = 328,
        TH_KEY_KP_9              = 329,
        TH_KEY_KP_DECIMAL       =  330,
        TH_KEY_KP_DIVIDE        =  331,
        TH_KEY_KP_MULTIPLY       = 332,
        TH_KEY_KP_SUBTRACT        = 333,
        TH_KEY_KP_ADD             = 334,
        TH_KEY_KP_ENTER          = 335,
        TH_KEY_KP_EQUAL           = 336,
        TH_KEY_LEFT_SHIFT        =  340,
        TH_KEY_LEFT_CONTROL      = 341,
        TH_KEY_LEFT_ALT          = 342,
        TH_KEY_LEFT_SUPER        = 343,
        TH_KEY_RIGHT_SHIFT       = 344,
        TH_KEY_RIGHT_CONTROL      = 345,
        TH_KEY_RIGHT_ALT          = 346,
        TH_KEY_RIGHT_SUPER       = 347,
        TH_KEY_MENU              = 348
    }
}
