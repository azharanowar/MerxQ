#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

using namespace std;

/**
 * Utility class providing common functions for the MerxQ system
 * Includes: ANSI color formatting, display helpers, input validation
 */
class Utils {
public:
    // ============================================
    // ANSI COLOR & FORMATTING
    // ============================================
    
    /**
     * Apply ANSI color codes to text
     * @param text - The text to colorize
     * @param color - Text color (red, green, yellow, blue, magenta, cyan, white)
     * @param bgColor - Background color (optional)
     * @param style - Text style: bold, dim, underline (optional)
     * @return Formatted string with ANSI codes
     */
    static string colorText(const string& text, const string& color = "", 
                           const string& bgColor = "", const string& style = "");
    
    // ============================================
    // DISPLAY FUNCTIONS
    // ============================================
    
    /**
     * Display main header with title
     * Example: ╔═══════════════════════════════╗
     *          ║     MerxQ Shop System        ║
     *          ╚═══════════════════════════════╝
     */
    static void showMainHeader(const string& title);
    
    /**
     * Display sub-header (smaller section title)
     */
    static void showSubHeader(const string& subtitle);
    
    /**
     * Clear the console screen
     */
    static void clearScreen();
    
    /**
     * Pause and wait for user to press Enter
     */
    static void pauseScreen();
    
    /**
     * Show loading animation with dots
     * @param message - Loading message to display
     * @param seconds - Duration of animation
     */
    static void showLoading(const string& message, int seconds = 2);
    
    // ============================================
    // INPUT VALIDATION (To be implemented)
    // ============================================
    
    /**
     * Get validated integer input within a range
     * @param prompt - Message to display
     * @param min - Minimum valid value
     * @param max - Maximum valid value
     * @return Valid integer
     */
    static int getIntInput(const string& prompt, int min, int max);
    
    /**
     * Get validated double input within a range
     */
    static double getDoubleInput(const string& prompt, double min, double max);
    
    /**
     * Get non-empty string input
     */
    static string getStringInput(const string& prompt);
    
    /**
     * Get valid choice from menu options
     */
    static int getMenuChoice(const string& prompt, int minOption, int maxOption);
};

#endif // UTILS_H
