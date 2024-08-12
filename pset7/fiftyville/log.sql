-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find first clues. clues found: mentioning of bakery, 3 witnesses, littering time 16:36
SELECT description
FROM crime_scene_reports
WHERE day = 28
AND month = 7
AND year = 2023
AND street = "Humphrey Street";

-- 4 cars exited
SELECT activity, license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2023
AND hour = 16;

/*
+----------+---------------+
| activity | license_plate |
+----------+---------------+
| exit     | WD5M8I6       |
| exit     | 4468KVT       |
| exit     | 207W38T       |
| exit     | C194752       |
+----------+---------------+
*/

-- 2 important statements
SELECT name, transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year = 2023;

/*
    Eugene saw the tief by the ATM at Leggett Street withdrawing money in this morning

    Raymond heard that the thief was in a call for less than a minute and said that he
    and another person are going to take the earliest flight out of Fiftyville tomorrow.
    The other person is going to buy the ticket
*/

-- 9 phone calls found
SELECT caller, receiver
FROM phone_calls
WHERE day = 28
AND month = 7
AND year = 2023
AND duration < 60;

/*
+----------------+----------------+
|     caller     |    receiver    |
+----------------+----------------+
| (130) 555-0289 | (996) 555-8899 |
| (499) 555-9472 | (892) 555-8872 |
| (367) 555-5533 | (375) 555-8161 |
| (499) 555-9472 | (717) 555-1342 |
| (286) 555-6063 | (676) 555-6554 |
| (770) 555-1861 | (725) 555-3243 |
| (031) 555-6622 | (910) 555-3251 |
| (826) 555-1652 | (066) 555-9701 |
| (338) 555-6650 | (704) 555-2131 |
+----------------+----------------+
*/

-- found 8 account numbers
SELECT account_number
FROM atm_transactions
WHERE day = 28
AND month = 7
AND year = 2023
AND transaction_type = "withdraw"
AND atm_location = "Leggett Street";

/*
+----------------+
| account_number |
+----------------+
| 28500762       |
| 28296815       |
| 76054385       |
| 49610011       |
| 16153065       |
| 25506511       |
| 81061156       |
| 26013199       |
+----------------+
*/

-- Get peoples informations that withdrew money this day at that location
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE day = 28
        AND month = 7
        AND year = 2023
        AND transaction_type = "withdraw"
        AND atm_location = "Leggett Street"
    )
);

/*
+---------+----------------+-----------------+---------------+
|  name   |  phone_number  | passport_number | license_plate |
+---------+----------------+-----------------+---------------+
| Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
| Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| Brooke  | (122) 555-4581 | 4408372428      | QX4YZN3       |
| Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
| Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+---------+----------------+-----------------+---------------+
*/

-- Tried the query from before but added the phone number to narrow the results
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE day = 28
        AND month = 7
        AND year = 2023
        AND transaction_type = "withdraw"
        AND atm_location = "Leggett Street"
    )
)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE day = 28
    AND month = 7
    AND year = 2023
    AND duration < 60
);

/*
+---------+----------------+-----------------+---------------+
|  name   |  phone_number  | passport_number | license_plate |
+---------+----------------+-----------------+---------------+
| Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+---------+----------------+-----------------+---------------+
*/

/* Tried to add the license_plates from the bakery
    but there were no results for 16:00 and 15:00
    -> Probably a stolen car or the other guys car
*/
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE day = 28
        AND month = 7
        AND year = 2023
        AND transaction_type = "withdraw"
        AND atm_location = "Leggett Street"
    )
)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE day = 28
    AND month = 7
    AND year = 2023
    AND duration < 60
)
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2023
    AND hour = 16
);

/* Those are the suspects
+---------+----------------+-----------------+---------------+
|  name   |  phone_number  | passport_number | license_plate |
+---------+----------------+-----------------+---------------+
| Kenny   | (826) 555-1652 | 9878712108      | 30G67EN       |
| Benista | (338) 555-6650 | 9586786673      | 8X428L0       |
| Taylor  | (286) 555-6063 | 1988161715      | 1106N58       |
| Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
| Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
+---------+----------------+-----------------+---------------+
*/

-- I want to get all informations about the local airport
SELECT id, full_name, abbreviation
FROM airports
WHERE city = "Fiftyville";

/*
+----+-----------------------------+--------------+
| id |          full_name          | abbreviation |
+----+-----------------------------+--------------+
| 8  | Fiftyville Regional Airport | CSF          |
+----+-----------------------------+--------------+
*/

-- Get all morning flights and their details
SELECT id, destination_airport_id, hour, minute
FROM flights
WHERE origin_airport_id = 8
AND day = 29
AND month = 7
AND year = 2023
AND hour <= 12;

/* The earliest flight is 8:20 and they will probably take it
+----+------------------------+------+--------+
| id | destination_airport_id | hour | minute |
+----+------------------------+------+--------+
| 23 | 11                     | 12   | 15     |
| 36 | 4                      | 8    | 20     |
| 43 | 1                      | 9    | 30     |
+----+------------------------+------+--------+
*/

-- Shrink the amount of suspects even more down by adding the passport number
SELECT name, phone_number, passport_number, license_plate
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE day = 28
        AND month = 7
        AND year = 2023
        AND transaction_type = "withdraw"
        AND atm_location = "Leggett Street"
    )
)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE day = 28
    AND month = 7
    AND year = 2023
    AND duration < 60
)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36
);

/* 3 suspects left
+--------+----------------+-----------------+---------------+
|  name  |  phone_number  | passport_number | license_plate |
+--------+----------------+-----------------+---------------+
| Kenny  | (826) 555-1652 | 9878712108      | 30G67EN       |
| Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
| Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+----------------+-----------------+---------------+
*/

-- I tried this query again but without the hours and found narrowed down to 2 suspects
SELECT id, name, phone_number, passport_number, license_plate
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE day = 28
        AND month = 7
        AND year = 2023
        AND transaction_type = "withdraw"
        AND atm_location = "Leggett Street"
    )
)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE day = 28
    AND month = 7
    AND year = 2023
    AND duration < 60
)
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND year = 2023
);

/* Diana isn't in the suspect list so only Bruce and Taylor are left
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 449774 | Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
| 514354 | Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
| 686048 | Bruce  | (367) 555-5533 | 5773159633      | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+
*/

-- Get the receiver phone number
SELECT caller, receiver, duration
FROM phone_calls
WHERE day = 28
AND month = 7
AND year = 2023
AND duration < 60
AND (caller = "(286) 555-6063" OR caller = "(367) 555-5533");

/*
+----------------+----------------+----------+
|     caller     |    receiver    | duration |
+----------------+----------------+----------+
| (367) 555-5533 | (375) 555-8161 | 45       |
| (286) 555-6063 | (676) 555-6554 | 43       |
+----------------+----------------+----------+
*/

-- Enter both receiver numbers and check for personal details
SELECT id, name, passport_number, license_plate, phone_number
FROM people
WHERE phone_number = "(375) 555-8161" OR phone_number = "(676) 555-6554)";

/* Only one results means: the thief must be Bruce and the accomplice is Robin
+--------+-------+-----------------+---------------+----------------+
|   id   | name  | passport_number | license_plate |  phone_number  |
+--------+-------+-----------------+---------------+----------------+
| 864400 | Robin | NULL            | 4V16VO0       | (375) 555-8161 |
+--------+-------+-----------------+---------------+----------------+
*/


SELECT abbreviation, full_name, city
FROM airports
WHERE id = 4;

/* Bruce, New York City, Robin
+--------------+-------------------+---------------+
| abbreviation |     full_name     |     city      |
+--------------+-------------------+---------------+
| LGA          | LaGuardia Airport | New York City |
+--------------+-------------------+---------------+
*/
