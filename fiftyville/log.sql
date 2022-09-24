-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Get the description about the crime
SELECT
    description
    , year
    , month
    , day
FROM
    crime_scene_reports
WHERE
    year = 2021
AND
    month = 7
AND
    day = 28
AND
    street = "Humphrey Street";

/*
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+------+-------+-----+
|                                                                                                       description                                                                                                        | year | month | day |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+------+-------+-----+
| Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. | 2021 | 7     | 28  |
| Littering took place at 16:36. No known witnesses.                                                                                                                                                                       | 2021 | 7     | 28  |
+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+------+-------+-----+
*/

-- Get information about interviews
SELECT
    name
    , year
    , month
    , day
    , transcript
FROM
    interviews
WHERE
    year = 2021
AND
    month = 7
AND
    day = 28
AND
    transcript LIKE "%bakery%";

/*
+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
|  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
| Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
| Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
| Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
*/

-- Get information about atm
SELECT
    account_number
    , year
    , month
    , day
    , amount
FROM
    atm_transactions
WHERE
    year = 2021
AND
    month = 7
AND
    day = 28
AND
    atm_location = "Leggett Street"
AND
    transaction_type = "withdraw";

/*
+----------------+------+-------+-----+--------+
| account_number | year | month | day | amount |
+----------------+------+-------+-----+--------+
| 28500762       | 2021 | 7     | 28  | 48     |
| 28296815       | 2021 | 7     | 28  | 20     |
| 76054385       | 2021 | 7     | 28  | 60     |
| 49610011       | 2021 | 7     | 28  | 50     |
| 16153065       | 2021 | 7     | 28  | 80     |
| 25506511       | 2021 | 7     | 28  | 20     |
| 81061156       | 2021 | 7     | 28  | 30     |
| 26013199       | 2021 | 7     | 28  | 35     |
+----------------+------+-------+-----+--------+
*/

-- Get person_id based on bank acount
SELECT
    bank_accounts.account_number
    , person_id
FROM
    bank_accounts
JOIN
    atm_transactions
ON
    bank_accounts.account_number = atm_transactions.account_number
WHERE
    bank_accounts.account_number IN (SELECT
                            account_number
                        FROM
                            atm_transactions
                        WHERE
                            year = 2021
                        AND
                            month = 7
                        AND
                            day = 28
                        AND
                            atm_location = "Leggett Street"
                        AND
                            transaction_type = "withdraw")
GROUP BY
    bank_accounts.account_number;

/*
+----------------+-----------+
| account_number | person_id |
+----------------+-----------+
| 16153065       | 458378    |
| 25506511       | 396669    |
| 26013199       | 514354    |
| 28296815       | 395717    |
| 28500762       | 467400    |
| 49610011       | 686048    |
| 76054385       | 449774    |
| 81061156       | 438727    |
+----------------+-----------+
*/


-- Get information about bakery
SELECT
    year
    , month
    , day
    , hour
    , minute
    , license_plate
FROM
    bakery_security_logs
WHERE
    year = 2021
AND
    month = 7
AND
    day = 28
AND
    hour = 10
AND
    minute <= 25
AND
    activity = "exit";

/*
+------+-------+-----+------+--------+---------------+
| year | month | day | hour | minute | license_plate |
+------+-------+-----+------+--------+---------------+
| 2021 | 7     | 28  | 10   | 16     | 5P2BI95       |
| 2021 | 7     | 28  | 10   | 18     | 94KL13X       |
| 2021 | 7     | 28  | 10   | 18     | 6P58WS2       |
| 2021 | 7     | 28  | 10   | 19     | 4328GD8       |
| 2021 | 7     | 28  | 10   | 20     | G412CB7       |
| 2021 | 7     | 28  | 10   | 21     | L93JTIZ       |
| 2021 | 7     | 28  | 10   | 23     | 322W7JE       |
| 2021 | 7     | 28  | 10   | 23     | 0NTHK55       |
+------+-------+-----+------+--------+---------------+
*/

-- Get personal information from license plate
SELECT
    people.license_plate
    , name
    , phone_number
    , passport_number
FROM
    people
JOIN
    bakery_security_logs
ON
    people.license_plate = bakery_security_logs.license_plate
WHERE
    year = 2021
AND
    month = 7
AND
    day = 28
AND
    hour = 10
AND
    minute <= 25
AND
    activity = "exit";
/*
+---------------+---------+----------------+-----------------+
| license_plate |  name   |  phone_number  | passport_number |
+---------------+---------+----------------+-----------------+
| 5P2BI95       | Vanessa | (725) 555-4692 | 2963008352      |
| 94KL13X       | Bruce   | (367) 555-5533 | 5773159633      |
| 6P58WS2       | Barry   | (301) 555-4174 | 7526138472      |
| 4328GD8       | Luca    | (389) 555-5198 | 8496433585      |
| G412CB7       | Sofia   | (130) 555-0289 | 1695452385      |
| L93JTIZ       | Iman    | (829) 555-5269 | 7049073643      |
| 322W7JE       | Diana   | (770) 555-1861 | 3592750733      |
| 0NTHK55       | Kelsey  | (499) 555-9472 | 8294398571      |
+---------------+---------+----------------+-----------------+
*/

-- Get information from phone call
SELECT
    caller
    , receiver
    , year
    , day
    , duration
FROM
    phone_calls
WHERE
    year = 2021
AND
    month = 7
AND
    day = 28
AND
    duration <= 60;

/*
+----------------+----------------+------+-----+----------+
|     caller     |    receiver    | year | day | duration |
+----------------+----------------+------+-----+----------+
| (130) 555-0289 | (996) 555-8899 | 2021 | 28  | 51       |
| (499) 555-9472 | (892) 555-8872 | 2021 | 28  | 36       |
| (367) 555-5533 | (375) 555-8161 | 2021 | 28  | 45       |
| (609) 555-5876 | (389) 555-5198 | 2021 | 28  | 60       |
| (499) 555-9472 | (717) 555-1342 | 2021 | 28  | 50       |
| (286) 555-6063 | (676) 555-6554 | 2021 | 28  | 43       |
| (770) 555-1861 | (725) 555-3243 | 2021 | 28  | 49       |
| (031) 555-6622 | (910) 555-3251 | 2021 | 28  | 38       |
| (826) 555-1652 | (066) 555-9701 | 2021 | 28  | 55       |
| (338) 555-6650 | (704) 555-2131 | 2021 | 28  | 54       |
+----------------+----------------+------+-----+----------+
*/

-- Merge personal information and phone information
SELECT
    name
    , phone_number
    , passport_number
FROM
    people
WHERE
    phone_number = "(375) 555-8161"
OR
    phone_number = "(996) 555-8899";

/*
+-------+----------------+-----------------+
| name  |  phone_number  | passport_number |
+-------+----------------+-----------------+
| Jack  | (996) 555-8899 | 9029462229      |
| Robin | (375) 555-8161 |                 |
+-------+----------------+-----------------+
+---------------+--------+----------------+-----------------+
| license_plate |  name  |  phone_number  | passport_number |
+---------------+--------+----------------+-----------------+
| 94KL13X       | Bruce  | (367) 555-5533 | 5773159633      |
| G412CB7       | Sofia  | (130) 555-0289 | 1695452385      |
| 322W7JE       | Diana  | (770) 555-1861 | 3592750733      |
| 0NTHK55       | Kelsey | (499) 555-9472 | 8294398571      |
+---------------+--------+----------------+-----------------+
*/

-- information about ACCOMPLIC based on receiver phone number
SELECT
    people.license_plate
    , name
    , phone_number
    , passport_number
FROM
    people
JOIN
    bakery_security_logs
ON
    people.license_plate = bakery_security_logs.license_plate
WHERE
    year = 2021
AND
    month = 7
AND
    day = 28
AND
    hour = 10
AND
    minute <= 25
AND
    activity = "exit"
AND phone_number IN (
    SELECT
    caller AS phone_number
FROM
    phone_calls
WHERE
    year = 2021
AND
    month = 7
AND
    day = 28
AND
    duration <= 60
);

-- Get information criminals use tomorrow flight
SELECT
    year
    , month
    , day
    , hour
    , minute
    , destination_airport_id
    , flights.id
FROM
    flights
JOIN
    airports
ON
    flights.origin_airport_id = airports.id
JOIN
    passengers
ON
    flights.id = passengers.flight_id
WHERE
    year = 2021
AND
    month = 7
AND
    day = 29
AND
    city = "Fiftyville"
ORDER BY
    hour,
    minute
LIMIT 1;
/*
+------+-------+-----+------+--------+------------------------+----+
| year | month | day | hour | minute | destination_airport_id | id |
+------+-------+-----+------+--------+------------------------+----+
| 2021 | 7     | 29  | 8    | 20     | 4                      | 36 |
+------+-------+-----+------+--------+------------------------+----+
*/

-- Get passengers
SELECT
    passport_number
FROM
    passengers
WHERE
    flight_id = 36;
/*
+-----------------+
| passport_number |
+-----------------+
| 7214083635      |
| 1695452385      |
| 5773159633      |
| 1540955065      |
| 8294398571      |
| 1988161715      |
| 9878712108      |
| 8496433585      |
+-----------------+
*/

-- Destination
SELECT
    full_name
    , city
FROM
    airports
WHERE
    id = 4;
/*
+-------------------+---------------+
|     full_name     |     city      |
+-------------------+---------------+
| LaGuardia Airport | New York City |
+-------------------+---------------+
*/

/*
Maybe criminal
+---------------+--------+----------------+-----------------+
| license_plate |  name  |  phone_number  | passport_number |
+---------------+--------+----------------+-----------------+
| 94KL13X       | Bruce  | (367) 555-5533 | 5773159633      |
| G412CB7       | Sofia  | (130) 555-0289 | 1695452385      |
+---------------+--------+----------------+-----------------+
