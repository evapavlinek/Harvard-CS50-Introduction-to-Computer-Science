-- list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in, starting with the highest rated
SELECT title
FROM movies
INNER JOIN (
    SELECT *
    FROM ratings
    WHERE movie_id IN (
        SELECT movie_id
        FROM stars
        WHERE person_id IN (
            SELECT id
            FROM people
            WHERE name == "Chadwick Boseman"
            )
        )
    ORDER BY rating DESC
    LIMIT 5
    ) ON id = movie_id;


--SELECT title FROM movies
--INNER JOIN ratings ON movies.id = ratings.movie_id
--INNER JOIN stars ON movies.id = stars.movie_id
--INNER JOIN people ON stars.person_id = people.id
--WHERE people.name = "Chadwick Boseman"
--ORDER BY rating DESC
--LIMIT 5;
