select distinct p.name from movies m
join directors d on m.id = d.movie_id
join people p on d.person_id = p.id
join ratings r on m.id = r.movie_id
where r.rating >= 9.0;