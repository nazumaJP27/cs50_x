SELECT DISTINCT title FROM movies
JOIN stars ON movies.id = stars.movie_id
WHERE id IN
(
    SELECT movie_id FROM stars
    WHERE person_id IN
    (
        SELECT id FROM people
        WHERE people.name = 'Bradley Cooper'
        OR people.name = 'Jennifer Lawrence'
    )
    GROUP BY movie_id
    HAVING COUNT(DISTINCT person_id) = 2
);
