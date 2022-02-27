/**
 * @brief Inits the relay.
 * 
 * @param relayPin Relat pin.
 */
void initRelay(int relayPin);

/**
 * @brief Verifies if the relay is closed.
 * 
 * @param relayPin Relay pin.
 * @return true  when the relay is closed.
 * @return false  when the relay is open.
 */
bool isRelayClosed(int relayPin);

/**
 * @brief Turns on the shop vac.
 * 
 * @param relayPin Relay Pin.
 */
void turnOnShopVac(int relayPin);

/**
 * @brief Turns off the shop vac.
 * 
 * @param relayPin Relay pin.
 * @param d Seconds before turn it off.
 */
void turnOffShopVac(int relayPin, int d);
