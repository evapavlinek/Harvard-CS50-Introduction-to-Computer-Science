-- list the names of all people who starred in a movie in which Kevin Bacon also starred
-- only select the Kevin Bacon born in 1958
-- Kevin Bacon himself should not be included in the resulting list
SELECT name
FROM people
WHERE NOT name == "Kevin Bacon" AND id IN (
    SELECT person_id
    FROM stars
    WHERE movie_id IN (
        SELECT movie_id
        FROM stars
        WHERE person_id IN (
            SELECT id
            FROM people
            WHERE name == "Kevin Bacon" AND birth == 1958
            )
        )
    );
