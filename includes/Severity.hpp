#pragma once

enum SEVERITY { LOW, MODERATE, HIGH, PARAMOUNT };

/*
 * LOW
 *  * Drive through orders
 *  * Uber eats who do NOT have a driver associated with them (flaw in Uber
 * Eats) MODERATE
 *  * Newly created mobile orders
 *  * Newly created cafe orders when cafe order count is high
 * HIGH
 *  * Cafe orders with low cafe order count and low drive through count
 *  * Uber eats with an associated driver
 *  * Mobile orders created after 2 minutes
 * PARAMOUNT
 *  * Orders from all generators that have a time since epoch greater than 6
 * minutes. Cafe has higher priority than drive in this instance
 */
