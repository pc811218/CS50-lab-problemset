select p.name from movies m
join stars s on m.id = s.movie_id
join people p on s.person_id = p.id
where m.title = 'Toy Story';