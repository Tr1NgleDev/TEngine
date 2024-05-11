#pragma once

#undef DELETE

namespace TEngine
{
    enum class Keys : int
	{
        UNKNOWN = GLFW_KEY_UNKNOWN,              
        SPACE = GLFW_KEY_SPACE,                  
        APOSTROPHE = GLFW_KEY_APOSTROPHE,        
        COMMA = GLFW_KEY_COMMA,                  
        MINUS = GLFW_KEY_MINUS,                  
        PERIOD = GLFW_KEY_PERIOD,                
        SLASH = GLFW_KEY_SLASH,                  
        K0 = GLFW_KEY_0,                         
        K1 = GLFW_KEY_1,                         
        K2 = GLFW_KEY_2,                         
        K3 = GLFW_KEY_3,                         
        K4 = GLFW_KEY_4,                         
        K5 = GLFW_KEY_5,                         
        K6 = GLFW_KEY_6,                         
        K7 = GLFW_KEY_7,                         
        K8 = GLFW_KEY_8,                         
        K9 = GLFW_KEY_9,                         
        SEMICOLON = GLFW_KEY_SEMICOLON,          
        EQUAL = GLFW_KEY_EQUAL,                  
        A = GLFW_KEY_A,                          
        B = GLFW_KEY_B,                          
        C = GLFW_KEY_C,                          
        D = GLFW_KEY_D,                          
        E = GLFW_KEY_E,                          
        F = GLFW_KEY_F,                          
        G = GLFW_KEY_G,                          
        H = GLFW_KEY_H,                          
        I = GLFW_KEY_I,                          
        J = GLFW_KEY_J,                          
        K = GLFW_KEY_K,                          
        L = GLFW_KEY_L,                          
        M = GLFW_KEY_M,                          
        N = GLFW_KEY_N,                          
        O = GLFW_KEY_O,                          
        P = GLFW_KEY_P,                          
        Q = GLFW_KEY_Q,                          
        R = GLFW_KEY_R,                          
        S = GLFW_KEY_S,                          
        T = GLFW_KEY_T,                          
        U = GLFW_KEY_U,                          
        V = GLFW_KEY_V,                          
        W = GLFW_KEY_W,                          
        X = GLFW_KEY_X,                          
        Y = GLFW_KEY_Y,                          
        Z = GLFW_KEY_Z,                          
        LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,    
        BACKSLASH = GLFW_KEY_BACKSLASH,          
        RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,  
        GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,    
        WORLD_1 = GLFW_KEY_WORLD_1,              
        WORLD_2 = GLFW_KEY_WORLD_2,              
        ESCAPE = GLFW_KEY_ESCAPE,                
        ENTER = GLFW_KEY_ENTER,                  
        TAB = GLFW_KEY_TAB,                      
        BACKSPACE = GLFW_KEY_BACKSPACE,          
        INSERT = GLFW_KEY_INSERT,                
        DELETE = GLFW_KEY_DELETE,                
        RIGHT = GLFW_KEY_RIGHT,                  
        LEFT = GLFW_KEY_LEFT,                    
        DOWN = GLFW_KEY_DOWN,                    
        UP = GLFW_KEY_UP,                        
        PAGE_UP = GLFW_KEY_PAGE_UP,              
        PAGE_DOWN = GLFW_KEY_PAGE_DOWN,          
        HOME = GLFW_KEY_HOME,                    
        END = GLFW_KEY_END,                      
        CAPS_LOCK = GLFW_KEY_CAPS_LOCK,          
        SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,      
        NUM_LOCK = GLFW_KEY_NUM_LOCK,            
        PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,    
        PAUSE = GLFW_KEY_PAUSE,                  
        F1 = GLFW_KEY_F1,                        
        F2 = GLFW_KEY_F2,                        
        F3 = GLFW_KEY_F3,                        
        F4 = GLFW_KEY_F4,                        
        F5 = GLFW_KEY_F5,                        
        F6 = GLFW_KEY_F6,                        
        F7 = GLFW_KEY_F7,                        
        F8 = GLFW_KEY_F8,                        
        F9 = GLFW_KEY_F9,                        
        F10 = GLFW_KEY_F10,                      
        F11 = GLFW_KEY_F11,                      
        F12 = GLFW_KEY_F12,                      
        F13 = GLFW_KEY_F13,                      
        F14 = GLFW_KEY_F14,                      
        F15 = GLFW_KEY_F15,                      
        F16 = GLFW_KEY_F16,                      
        F17 = GLFW_KEY_F17,                      
        F18 = GLFW_KEY_F18,                      
        F19 = GLFW_KEY_F19,                      
        F20 = GLFW_KEY_F20,                      
        F21 = GLFW_KEY_F21,                      
        F22 = GLFW_KEY_F22,                      
        F23 = GLFW_KEY_F23,                      
        F24 = GLFW_KEY_F24,                      
        F25 = GLFW_KEY_F25,                      
        KP_0 = GLFW_KEY_KP_0,                    
        KP_1 = GLFW_KEY_KP_1,                    
        KP_2 = GLFW_KEY_KP_2,                    
        KP_3 = GLFW_KEY_KP_3,                    
        KP_4 = GLFW_KEY_KP_4,                    
        KP_5 = GLFW_KEY_KP_5,                    
        KP_6 = GLFW_KEY_KP_6,                    
        KP_7 = GLFW_KEY_KP_7,                    
        KP_8 = GLFW_KEY_KP_8,                    
        KP_9 = GLFW_KEY_KP_9,                    
        KP_DECIMAL = GLFW_KEY_KP_DECIMAL,        
        KP_DIVIDE = GLFW_KEY_KP_DIVIDE,          
        KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,      
        KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,      
        KP_ADD = GLFW_KEY_KP_ADD,                
        KP_ENTER = GLFW_KEY_KP_ENTER,            
        KP_EQUAL = GLFW_KEY_KP_EQUAL,            
        LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,        
        LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,    
        LEFT_ALT = GLFW_KEY_LEFT_ALT,            
        LEFT_SUPER = GLFW_KEY_LEFT_SUPER,        
        RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,      
        RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,  
        RIGHT_ALT = GLFW_KEY_RIGHT_ALT,          
        RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,      
        MENU = GLFW_KEY_MENU
    };

    inline std::string Keys_to_string(const Keys v)
	{
        switch (v)
    	{
        case Keys::UNKNOWN: 
        {
            return "UNKNOWN";
        }
        case Keys::SPACE: 
        {
            return "SPACE";
        }
        case Keys::APOSTROPHE: 
        {
            return "APOSTROPHE";
        }
        case Keys::COMMA: 
        {
            return "COMMA";
        }
        case Keys::MINUS: 
        {
            return "MINUS";
        }
        case Keys::PERIOD: 
        {
            return "PERIOD";
        }
        case Keys::SLASH: 
        {
            return "SLASH";
        }
        case Keys::K0: 
        {
            return "K0";
        }
        case Keys::K1: 
        {
            return "K1";
        }
        case Keys::K2: 
        {
            return "K2";
        }
        case Keys::K3: 
        {
            return "K3";
        }
        case Keys::K4: 
        {
            return "K4";
        }
        case Keys::K5: 
        {
            return "K5";
        }
        case Keys::K6: 
        {
            return "K6";
        }
        case Keys::K7: 
        {
            return "K7";
        }
        case Keys::K8: 
        {
            return "K8";
        }
        case Keys::K9: 
        {
            return "K9";
        }
        case Keys::SEMICOLON: 
        {
            return "SEMICOLON";
        }
        case Keys::EQUAL: 
        {
            return "EQUAL";
        }
        case Keys::A: 
        {
            return "A";
        }
        case Keys::B: 
        {
            return "B";
        }
        case Keys::C: 
        {
            return "C";
        }
        case Keys::D: 
        {
            return "D";
        }
        case Keys::E: 
        {
            return "E";
        }
        case Keys::F: 
        {
            return "F";
        }
        case Keys::G: 
        {
            return "G";
        }
        case Keys::H: 
        {
            return "H";
        }
        case Keys::I: 
        {
            return "I";
        }
        case Keys::J: 
        {
            return "J";
        }
        case Keys::K: 
        {
            return "K";
        }
        case Keys::L: 
        {
            return "L";
        }
        case Keys::M: 
        {
            return "M";
        }
        case Keys::N: 
        {
            return "N";
        }
        case Keys::O: 
        {
            return "O";
        }
        case Keys::P: 
        {
            return "P";
        }
        case Keys::Q: 
        {
            return "Q";
        }
        case Keys::R: 
        {
            return "R";
        }
        case Keys::S: 
        {
            return "S";
        }
        case Keys::T: 
        {
            return "T";
        }
        case Keys::U: 
        {
            return "U";
        }
        case Keys::V: 
        {
            return "V";
        }
        case Keys::W: 
        {
            return "W";
        }
        case Keys::X: 
        {
            return "X";
        }
        case Keys::Y: 
        {
            return "Y";
        }
        case Keys::Z: 
        {
            return "Z";
        }
        case Keys::LEFT_BRACKET: 
        {
            return "LEFT_BRACKET";
        }
        case Keys::BACKSLASH: 
        {
            return "BACKSLASH";
        }
        case Keys::RIGHT_BRACKET: 
        {
            return "RIGHT_BRACKET";
        }
        case Keys::GRAVE_ACCENT: 
        {
            return "GRAVE_ACCENT";
        }
        case Keys::WORLD_1: 
        {
            return "WORLD_1";
        }
        case Keys::WORLD_2: 
        {
            return "WORLD_2";
        }
        case Keys::ESCAPE: 
        {
            return "ESCAPE";
        }
        case Keys::ENTER: 
        {
            return "ENTER";
        }
        case Keys::TAB: 
        {
            return "TAB";
        }
        case Keys::BACKSPACE: 
        {
            return "BACKSPACE";
        }
        case Keys::INSERT: 
        {
            return "INSERT";
        }
        case Keys::DELETE: 
        {
            return "DELETE";
        }
        case Keys::RIGHT: 
        {
            return "RIGHT";
        }
        case Keys::LEFT: 
        {
            return "LEFT";
        }
        case Keys::DOWN: 
        {
            return "DOWN";
        }
        case Keys::UP: 
        {
            return "UP";
        }
        case Keys::PAGE_UP: 
        {
            return "PAGE_UP";
        }
        case Keys::PAGE_DOWN: 
        {
            return "PAGE_DOWN";
        }
        case Keys::HOME: 
        {
            return "HOME";
        }
        case Keys::END: 
        {
            return "END";
        }
        case Keys::CAPS_LOCK: 
        {
            return "CAPS_LOCK";
        }
        case Keys::SCROLL_LOCK: 
        {
            return "SCROLL_LOCK";
        }
        case Keys::NUM_LOCK: 
        {
            return "NUM_LOCK";
        }
        case Keys::PRINT_SCREEN: 
        {
            return "PRINT_SCREEN";
        }
        case Keys::PAUSE: 
        {
            return "PAUSE";
        }
        case Keys::F1: 
        {
            return "F1";
        }
        case Keys::F2: 
        {
            return "F2";
        }
        case Keys::F3: 
        {
            return "F3";
        }
        case Keys::F4: 
        {
            return "F4";
        }
        case Keys::F5: 
        {
            return "F5";
        }
        case Keys::F6: 
        {
            return "F6";
        }
        case Keys::F7: 
        {
            return "F7";
        }
        case Keys::F8: 
        {
            return "F8";
        }
        case Keys::F9: 
        {
            return "F9";
        }
        case Keys::F10: 
        {
            return "F10";
        }
        case Keys::F11: 
        {
            return "F11";
        }
        case Keys::F12: 
        {
            return "F12";
        }
        case Keys::F13: 
        {
            return "F13";
        }
        case Keys::F14: 
        {
            return "F14";
        }
        case Keys::F15: 
        {
            return "F15";
        }
        case Keys::F16: 
        {
            return "F16";
        }
        case Keys::F17: 
        {
            return "F17";
        }
        case Keys::F18: 
        {
            return "F18";
        }
        case Keys::F19: 
        {
            return "F19";
        }
        case Keys::F20: 
        {
            return "F20";
        }
        case Keys::F21: 
        {
            return "F21";
        }
        case Keys::F22: 
        {
            return "F22";
        }
        case Keys::F23: 
        {
            return "F23";
        }
        case Keys::F24: 
        {
            return "F24";
        }
        case Keys::F25: 
        {
            return "F25";
        }
        case Keys::KP_0: 
        {
            return "KP_0";
        }
        case Keys::KP_1: 
        {
            return "KP_1";
        }
        case Keys::KP_2: 
        {
            return "KP_2";
        }
        case Keys::KP_3: 
        {
            return "KP_3";
        }
        case Keys::KP_4: 
        {
            return "KP_4";
        }
        case Keys::KP_5: 
        {
            return "KP_5";
        }
        case Keys::KP_6: 
        {
            return "KP_6";
        }
        case Keys::KP_7: 
        {
            return "KP_7";
        }
        case Keys::KP_8: 
        {
            return "KP_8";
        }
        case Keys::KP_9: 
        {
            return "KP_9";
        }
        case Keys::KP_DECIMAL: 
        {
            return "KP_DECIMAL";
        }
        case Keys::KP_DIVIDE: 
        {
            return "KP_DIVIDE";
        }
        case Keys::KP_MULTIPLY: 
        {
            return "KP_MULTIPLY";
        }
        case Keys::KP_SUBTRACT: 
        {
            return "KP_SUBTRACT";
        }
        case Keys::KP_ADD: 
        {
            return "KP_ADD";
        }
        case Keys::KP_ENTER: 
        {
            return "KP_ENTER";
        }
        case Keys::KP_EQUAL: 
        {
            return "KP_EQUAL";
        }
        case Keys::LEFT_SHIFT: 
        {
            return "LEFT_SHIFT";
        }
        case Keys::LEFT_CONTROL: 
        {
            return "LEFT_CONTROL";
        }
        case Keys::LEFT_ALT: 
        {
            return "LEFT_ALT";
        }
        case Keys::LEFT_SUPER: 
        {
            return "LEFT_SUPER";
        }
        case Keys::RIGHT_SHIFT: 
        {
            return "RIGHT_SHIFT";
        }
        case Keys::RIGHT_CONTROL: 
        {
            return "RIGHT_CONTROL";
        }
        case Keys::RIGHT_ALT: 
        {
            return "RIGHT_ALT";
        }
        case Keys::RIGHT_SUPER: 
        {
            return "RIGHT_SUPER";
        }
        case Keys::MENU: 
        {
            return "MENU";
        }
        default:
        {
        	return"UNKNOWN";
        }
        }
    }
}

namespace std
{
    inline std::string to_string(const TEngine::Keys& key) noexcept
    {
        return TEngine::Keys_to_string(key);
    }
}
