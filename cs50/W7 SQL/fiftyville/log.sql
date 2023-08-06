-- Keep a log of any SQL queries you execute as you solve the mystery.

select * from crime_scene_reports where street = 'Humphrey Street' and month = 7 and day = 28;

-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

select * from interviews where month = 7 and day = 28 and transcript like '%thief%';

-- Ruth
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
-- If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- Eugene
-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- Raymond
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.

select * from bakery_security_logs where month = 7 and day = 28 and hour = 10 and minute between 15 and 25;

select * from atm_transactions where month = 7 and day = 28 and atm_location = 'Leggett Street'

select person_id from atm_transactions at
join bank_accounts ba on at.account_number = ba.account_number
where at.month = 7 and at.day = 28 and at.atm_location = 'Leggett Street'

select * from flights where month = 7 and day = 29 order by hour,minute limit 1;
-- flight_id = 36

select a.* from flights f
join airports a on f.destination_airport_id = a.id
where f.id = 36
;

select * from passengers
where flight_id = (
    select id from flights where month = 7 and day = 29 order by hour,minute limit 1
);

select * from people
where passport_number in (
    select passport_number from passengers
    where flight_id = (
        select id from flights where month = 7 and day = 29
        order by hour,minute limit 1
    )
)
and license_plate in (
    select license_plate
    from bakery_security_logs
    where month = 7 and day = 28 and hour = 10 and minute between 15 and 25
)
and id in (
    select person_id from atm_transactions at
    join bank_accounts ba on at.account_number = ba.account_number
    where at.month = 7 and at.day = 28 and at.atm_location = 'Leggett Street'
)

/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
| 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       | <---- thief
+--------+-------+----------------+-----------------+---------------+
*/

-- who talked to them for less than a minute.
select * from phone_calls
where month = 7 and day = 28
and caller in ('(389) 555-5198','(367) 555-5533');
and duration < 60

select * from people where phone_number in (
    select receiver from phone_calls
    where month = 7 and day = 28
    and caller = '(367) 555-5533'
    and duration < 60
)

/*
+--------+-------+----------------+-----------------+---------------+
|   id   | name  |  phone_number  | passport_number | license_plate |
+--------+-------+----------------+-----------------+---------------+
| 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       |  <---- accomplice
+--------+-------+----------------+-----------------+---------------+
*/