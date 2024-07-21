-- Keep a log of any SQL queries you execute as you solve the mystery.

-- All you know is that the theft took place on July 28, 2023 and that it took place on Humphrey Street.
SELECT *
FROM crime_scene_reports
WHERE year == 2023
    AND month == 7
    AND day = 28
    AND street == "Humphrey Street";

-- There are 2 cases for this particular date and street, but the one mentioning CS50 duck has an id 295.
-- Description of the crime: Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their
-- interview transcripts mentions the bakery.


-- What information can I get from the witnesses?
SELECT *
FROM interviews
WHERE year == 2023
    AND month == 7
    AND day = 28;
-- These are the comments witnesses gave:

-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery,
-- I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.


-- Notes:
-- Emma's bakery
-- security footage: car leaving at 10:15am - 10:25am
-- the thief withdrew money from an ATM on Leggett Street
-- thief is planning to take the earliest flight out of Fiftyville tomorrow
-- phone call lasted less than a minute
-- the person on the other end of the phone will purchase the flight ticket


-- List the license plates of the cars that were seen leaving in that time frame
SELECT license_plate
FROM bakery_security_logs
WHERE year == 2023
    AND month == 7
    AND day = 28
    AND hour == 10
    AND minute BETWEEN 10 AND 25
    AND activity == "exit";


-- List all account_numbers that withdrew money from the ATM on Leggett Street on that day
SELECT *
FROM atm_transactions
WHERE year == 2023
    AND month == 7
    AND day == 28
    AND atm_location == "Leggett Street"
    AND transaction_type == "withdraw";


-- List all phone calls that lasted less than a minute (info about the caller and receiver)
SELECT *
FROM phone_calls
WHERE year == 2023
    AND month == 7
    AND day == 28
    AND duration < 60;


-- Get the information about the airport the thief escaped to - New York City
SELECT *
FROM airports
WHERE id IN (
    SELECT destination_airport_id
    FROM flights
    WHERE origin_airport_id IN (
        SELECT id
        FROM airports
        WHERE city == "Fiftyville")
            AND year == 2023
            AND month == 7
            AND day == 29
        ORDER BY hour, minute
        LIMIT 1
        );


-- Notes:
-- flight id: 36
-- flight at 8:20


-- List all passport numbers from the passenegers on that flight
SELECT passport_number
FROM passengers
WHERE flight_id == 36;


-- List all people that were on that flight
SELECT *
FROM people
WHERE passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id == 36);


-- List the person that was on that flight and made a phone call at the time of the crime and has a car with the seen license plates and
-- withdrew the money at that time - Bruce
SELECT *
FROM people
WHERE id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year == 2023
            AND month == 7
            AND day == 28
            AND atm_location == "Leggett Street"
            AND transaction_type == "withdraw")
            AND person_id IN (
                SELECT id
                FROM people
                WHERE passport_number IN (
                    SELECT passport_number
                    FROM passengers
                    WHERE flight_id == 36
                    )
            AND phone_number IN (
                SELECT caller
                FROM phone_calls
                WHERE year == 2023
                    AND month == 7
                    AND day == 28
                    AND duration < 60
                    )
            AND license_plate IN (
                SELECT license_plate
                FROM bakery_security_logs
                WHERE year == 2023
                    AND month == 7
                    AND day = 28
                    AND hour == 10
                    AND minute BETWEEN 10 AND 25
                    AND activity == "exit"
                    )
        )
    );


-- Notes: Bruce's phone number is (367) 555-5533


-- List the person that he called when he committed the crime - Robin
SELECT *
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year == 2023
        AND month == 7
        AND day == 28
        AND duration < 60
        AND caller == "(367) 555-5533"
        );
