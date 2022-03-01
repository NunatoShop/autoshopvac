/**
 * @brief Inits the relay.
 */
void initRelay();

/**
 * @brief Verifies if the relay is closed.
 *
 * @return true  when the relay is closed.
 * @return false  when the relay is open.
 */
bool isRelayClosed();

/**
 * @brief Turns on the shop vac.
 * 
 */
void turnOnShopVac();

/**
 * @brief Turns off the shop vac.
 * 
 * @param d Seconds before turn it off.
 */
void turnOffShopVac(int d);
