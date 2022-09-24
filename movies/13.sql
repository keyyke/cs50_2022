SELECT
    people.name
FROM
    movies
JOIN
    stars
on
    movies.id = stars.movie_id
JOIN
    people
ON
    people.id = stars.person_id
WHERE
    movies.id IN (SELECT movies.id FROM movies JOIN stars on movies.id = stars.movie_id JOIN people ON people.id = stars.person_id WHERE people.name = "Kevin Bacon" AND people.birth = 1958)
GROUP BY
    people.name
HAVING
    people.name != "Kevin Bacon";
