SELECT AVG(energy) as "average energy" FROM songs
WHERE artist_id == ( SELECT id FROM artists WHERE name == "Drake");
