/**
 * @brief Inits the relay.
 */
void InitRelay();

/**
 * @brief Verifies if the shop vac is on.
 *
 * @return true  when the shop vac is on.
 * @return false  when the shop vac is off.
 */
bool IsShopVacOn();

/**
 * @brief Turns on the shop vac.
 * 
 */
void TurnOnShopVac();

/**
 * @brief Turns off the shop vac.
 * 
 * @param d Seconds before turn it off.
 */
void TurnOffShopVac(int d);
