-- Keep a log of any SQL queries you execute as you solve the mystery.
/*
-- Step 0: I've created a schema.txt file to have a quick way to look at the columns and informations
           for each table present in the fiftyville.db without the need to query `.tables` and `.schema`
           multiple times. Commands used: `echo ".tables" | sqlite3 fiftyville.db > schema.txt`
                                          `echo ".schema" | sqlite3 fiftyville.db >> schema.txt`

-- Step 1: The following is all the information we know from the crime:
               "... the theft took place on *July 28, 2024*
               and that it took place on *Humphrey Street*."

           As Carter suggested, we can start by checking the data from the `crime_scene_reports` table,
           running the query:
               `SELECT description
                FROM crime_scene_reports
                WHERE year = 2024
                AND month = 7
                AND day = 28
                AND street = 'Humphrey Street';`

           After running the query, we get additional information for the time and place:
               "... the theft took place on *July 28, 2024 - 10:15am*
               and that it took place at a *bakery* on *Humphrey Street*."

-- Step 2: Now that we know that the crime happened on the bakery at 10:15am and we happen to have a table
           called `bakery_security_logs`, we can check the data returned from a query targeting that:
               `SELECT *
                FROM bakery_security_logs
                WHERE year = 2024
                AND month = 7
                AND day = 28
                AND hour IN (9, 10);`

           The data returned from the query have given us information about license plates of vehicles that
           entered and exited the bakery in the time frame of 9am to 11am, but to narrow down the possible
           thief's license plate number, we could go back and check the interviewed witnesses.

-- Step 3: To get more information about what happened in the bakery, we may check the data returned from a
           query targeting the `interviews` table:
               `SELECT name, transcript
                FROM interviews
                WHERE year = 2024
                AND month = 7
                AND day = 28
                AND transcript LIKE '%bakery%';`

            After running the query, we have the following clues:
                - The thief left the bakery parking lot within 10min of the theft;
                - The thief was saw withdrawing money earlier in the morning at a ATM on Leggett Street;
                - "As the thief was leaving the bakery, they called someone who talked to them for less than a minute.",
                  they plan to take the earliest flight out of Fiftyville on 29 of July, and the thief asked the person
                  on the call to purchase the flight tickets.

-- Step 4: We can now use a query similar to the one we've already used in `bakery_security_logs`, to further narrow
           the possible license plate:
               `SELECT license_plate
                FROM bakery_security_logs
                WHERE year = 2024
                AND month = 7
                AND day = 28
                AND hour = 10
                AND minute BETWEEN 15 AND 25
                AND activity = 'exit';`

           We've got two more important peaces of information that can help us to start searching who is the
           accomplice and the thief's whereabout before entering the bakery.
           First, we'll target the `atm_transactions` table with the following query:
               `SELECT account_number
                FROM atm_transactions
                WHERE year = 2024
                AND month = 7
                AND day = 28
                AND atm_location = 'Leggett Street'
                AND transaction_type = 'withdraw';`

           The query returned eight account numbers, so we can't determine the thief's bank account yet.
           Our next query will target the `phone_calls` table, by the information we've got from the other
           witness interview:
               `SELECT caller, receiver
                FROM phone_calls
                WHERE year = 2024
                AND month = 7
                AND day = 28
                AND duration < 60;`

           After running those three queries in the respective tables, we have the following data:
               - 08 license plates;
               - 08 account numbers;
               - 08 phone numbers (callers)

-- Step 5: Now we will find informations about the first flight that departed from Fiftyville on
           July 29. First, we need the Fiftyville airport id, found in `airports`:
               `SELECT id
                FROM airports
                WHERE city = 'Fiftyville';`

           Then we use this id as the `origin_airport_id` on the `fligths` table to know the
           `destination_airport_id`:
               `SELECT destination_airport_id
                FROM flights
                WHERE origin_airport_id =
                (
                    SELECT id
                    FROM airports
                    WHERE city = 'Fiftyville'
                )
                AND year = 2024
                AND month = 7
                AND day = 29
                ORDER BY hour, minute
                LIMIT 1;`

           And now we find out the city using this airport id on the `airports` table:
               `SELECT city
                FROM airports
                WHERE id =
                (
                    SELECT destination_airport_id
                    FROM flights
                    WHERE origin_airport_id =
                    (
                        SELECT id
                        FROM airports
                        WHERE city = 'Fiftyville'
                    )
                    AND year = 2024
                    AND month = 7
                    AND day = 29
                    ORDER BY hour, minute
                    LIMIT 1
                );`

           We discovered that the first flight that left Fiftyville on July 29 was heading to New York.

-- Step 6: Now that we know what was the first flight, we can cross the passengers informations with the
           `passport_number` of people who their data matches up with the other returning data from our
           previous queries. But first, we need to narrow down the three lists of 8 values to one list
           of person information.

           We can achieve this by combining the three queries we used before with a new one:
               `SELECT *
                FROM people
                WHERE id IN
                (
                    SELECT person_id
                    FROM bank_accounts
                    WHERE account_number IN
                    (
                        SELECT account_number
                        FROM atm_transactions
                        WHERE year = 2024
                        AND month = 7
                        AND day = 28
                        AND atm_location = 'Leggett Street'
                        AND transaction_type = 'withdraw'
                    )
                )
                AND phone_number IN
                (
                    SELECT caller
                    FROM phone_calls
                    WHERE year = 2024
                    AND month = 7
                    AND day = 28
                    AND duration < 60
                )
                AND license_plate IN
                (
                    SELECT license_plate
                    FROM bakery_security_logs
                    WHERE year = 2024
                    AND month = 7
                    AND day = 28
                    AND hour = 10
                    AND minute BETWEEN 15 AND 25
                    AND activity = 'exit'
                );`


           Now we have two suspects: Diana and Bruce.

-- Step 7: We can use the `passport_number` from the two suspects to see which one was in the flight
           that left Fiftyville to NY. Let's start by grabbing the `flight_id` from `flights`:
               `SELECT id
                FROM flights
                WHERE origin_airport_id =
                (
                    SELECT id
                    FROM airports
                    WHERE city = 'Fiftyville'
                )
                AND destination_airport_id =
                (
                    SELECT id
                    FROM airports
                    WHERE city = 'New York City'
                )
                AND year = 2024
                AND month = 7
                AND day = 29
                ORDER BY hour, minute
                LIMIT 1;`

           Now combining with the `passport_number` in the `passengers` table:
               `SELECT *
                FROM passengers
                WHERE flight_id =
                (
                    SELECT id
                    FROM flights
                    WHERE origin_airport_id =
                    (
                        SELECT id
                        FROM airports
                        WHERE city = 'Fiftyville'
                    )
                    AND destination_airport_id =
                    (
                        SELECT id
                        FROM airports
                        WHERE city = 'New York City'
                    )
                    AND year = 2024
                    AND month = 7
                    AND day = 29
                    ORDER BY hour, minute
                    LIMIT 1
                )
                AND passport_number IN
                (
                    SELECT passport_number
                    FROM people
                    WHERE id IN
                    (
                        SELECT person_id
                        FROM bank_accounts
                        WHERE account_number IN
                        (
                            SELECT account_number
                            FROM atm_transactions
                            WHERE year = 2024
                            AND month = 7
                            AND day = 28
                            AND atm_location = 'Leggett Street'
                            AND transaction_type = 'withdraw'
                        )
                    )
                    AND phone_number IN
                    (
                        SELECT caller
                        FROM phone_calls
                        WHERE year = 2024
                        AND month = 7
                        AND day = 28
                        AND duration < 60
                    )
                    AND license_plate IN
                    (
                        SELECT license_plate
                        FROM bakery_security_logs
                        WHERE year = 2024
                        AND month = 7
                        AND day = 28
                        AND hour = 10
                        AND minute BETWEEN 15 AND 25
                        AND activity = 'exit'
                    )
                );`

           Bingo, the query returned only one record, so we can pinpoint the thief now!
               `SELECT name
                FROM people
                WHERE passport_number =
                (
                    SELECT passport_number
                    FROM passengers
                    WHERE flight_id =
                    (
                        SELECT id
                        FROM flights
                        WHERE origin_airport_id =
                        (
                            SELECT id
                            FROM airports
                            WHERE city = 'Fiftyville'
                        )
                        AND destination_airport_id =
                        (
                            SELECT id
                            FROM airports
                            WHERE city = 'New York City'
                        )
                        AND year = 2024
                        AND month = 7
                        AND day = 29
                        ORDER BY hour, minute
                        LIMIT 1
                    )
                    AND passport_number IN
                    (
                        SELECT passport_number
                        FROM people
                        WHERE id IN
                        (
                            SELECT person_id
                            FROM bank_accounts
                            WHERE account_number IN
                            (
                                SELECT account_number
                                FROM atm_transactions
                                WHERE year = 2024
                                AND month = 7
                                AND day = 28
                                AND atm_location = 'Leggett Street'
                                AND transaction_type = 'withdraw'
                            )
                        )
                        AND phone_number IN
                        (
                            SELECT caller
                            FROM phone_calls
                            WHERE year = 2024
                            AND month = 7
                            AND day = 28
                            AND duration < 60
                        )
                        AND license_plate IN
                        (
                            SELECT license_plate
                            FROM bakery_security_logs
                            WHERE year = 2024
                            AND month = 7
                            AND day = 28
                            AND hour = 10
                            AND minute BETWEEN 15 AND 25
                            AND activity = 'exit'
                        )
                    )
                );`

           The thief's name is Bruce.

-- Step 8: To findout who's the accomplice, we can begin by checking the number of the recever
           from that phone call in the bakery parking lot:
                `SELECT name
                 FROM people
                 WHERE phone_number =
                 (
                    SELECT receiver
                    FROM phone_calls
                    WHERE caller =
                    (
                        SELECT phone_number
                        FROM people
                        WHERE name = 'Bruce'
                    )
                    AND year = 2024
                    AND month = 7
                    AND day = 28
                    AND duration < 60
                 );`

           By the returning data from this query, we can point Robin as Bruce's accomplice.

-- Case Cleared.
*/


