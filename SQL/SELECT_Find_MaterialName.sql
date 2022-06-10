SELECT 
COALESCE(MINID,ICEID,GID,SALID,PIID,COID,MGID,RMID,T1ID,NCID,FBID,AMID) as ItemID,
COALESCE(MINName,ICEName,GName,SALName,PIName,COName,MGName,RMName,T1Name,NCName,FBName,AMName) as ItemName
from Material
left join Mineral on MINID = MATMINID
left join IceProduct on ICEID = MATICEID
left JOIN Gas on GID=MATGID
left JOIN Salvage on SALID=MATSALID
left JOIN PIProduct on PIID=MATPIID
left JOIN Commodity on COID=MATCOID
left JOIN MoonGoo on MGID=MATMGID
left JOIN ReactionMaterial on RMID=MATRMID
left JOIN T1Product on T1ID=MATT1ID
left JOIN NamedComponent on NCID=MATNCID
left JOIN FuelBlock on FBID=MATFBID
left JOIN AbyssalMaterial on AMID=MATAMID
where MatID = 30



