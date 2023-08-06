select avg(s.energy) from songs s
join artists a on s.artist_id = a.id
where a.name = 'Drake'
;