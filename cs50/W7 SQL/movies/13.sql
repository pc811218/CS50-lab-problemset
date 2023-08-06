select p.name from stars s
join people p on s.person_id = p.id
where s.movie_id in
(
    select s.movie_id from stars s
    join people p on s.person_id = p.id
    where p.name = 'Kevin Bacon' and p.birth = 1958
)
and not (p.name = 'Kevin Bacon' and p.birth = 1958);
