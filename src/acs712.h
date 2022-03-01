/**
 * @brief Get the current value.
 * 
 * @return int 
 */
int GetValue();

/**
 * @brief Get the current voltage.
 * 
 * @return float 
 */
float GetVoltage();

/**
 * @brief Get the Starting Voltage
 * 
 * @return float 
 */
float GetStartingVoltage();

/**
 * @brief checks changes in the connected tool and start or stop the shopvac.
 * 
 */
void CheckConnectedTool();