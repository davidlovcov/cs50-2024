SELECT movies.title, ratings.rating
FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE year = 2010
AND ratings.rating IS NOT NULL
ORDER BY rating DESC, title ASC;
