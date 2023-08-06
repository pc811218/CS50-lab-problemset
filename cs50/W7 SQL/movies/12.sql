select m.title from
(
    select s.movie_id from stars s
    join people p on s.person_id = p.id
    where p.name = 'Bradley Cooper'
) p1
join
(
    select s.movie_id from stars s
    join people p on s.person_id = p.id
    and p.name = 'Jennifer Lawrence'
) p2
on p1.movie_id = p2.movie_id
join movies m on p1.movie_id = m.id;
