#ifndef STAMPED_VALUE_HPP
#define STAMPED_VALUE_HPP


#include "plib/util/system.hpp"


template <typename T>
class StampedValue{

    public:

        StampedValue(T value, double timestamp);

        StampedValue(T value);

        // One-liner for updating the values
        void update(T value, double timestamp);

        // Updates the value and auto refreshes the timestamp
        void update(T value);

        /**
         * @brief Get the value this holds
         * 
         * @return `T` 
         */
        T get_value();

        /**
         * @brief Get the timestamp since the last update in seconds
         * 
         * @return `double` 
         */
        double get_timestamp();

        /**
         * @brief Get the rate of change since the last two updates
         * 
         * @return `double` 
         */
        double get_rate();

        /**
         * @brief Get the difference in values from current to previous
         * 
         * @return T
         */
        T get_dv();

        /**
         * @brief Get the difference in time since the last update and the one before that
         * 
         * @return `double` 
         */
        double get_dt();

    private:
    
        // The internal value to hold
        T m_value;

        // The timestamp in seconds
        double m_timestamp;

        // The previous internal value since `update()`
        T m_prev_value;

        // The previous timestamp since `update()` in seconds
        double m_prev_timestamp;

        
}; // class StampedValue


// Include implementation file `.tpp` for template methods
#include "plib/util/stamped_value.tpp"


#endif // STAMPED_VALUE