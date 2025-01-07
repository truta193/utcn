BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS Clients (id INTEGER PRIMARY KEY,name String,email String,password String,address String);
CREATE TABLE IF NOT EXISTS Orders (id INTEGER PRIMARY KEY,clientId int,productId int,quantity int,price Double);
CREATE TABLE IF NOT EXISTS Products (id INTEGER PRIMARY KEY,name String,price double,quantity int);
CREATE TABLE IF NOT EXISTS logs (id INTEGER PRIMARY KEY, order_id INTEGER);
INSERT INTO "Clients" ("id","name","email","password","address") VALUES (1,'Mihnea','mihnea@gmail.com','f6b7ceae29b9d96ab46b06b09f58861cfd6e00dc2546f350fb359349fa62ced4','Str. Plopilor 3'),
 (2,'George','george@yahoo.com','224db8f382e11c33fcc544bfdc367650206ed39c502aa91eeeab50e780d3c9e0','Str. Florilor 4'),
 (3,'Florin','florin1@yahoo.com','24dfb73241b21a08fc8dcb73438871e6709c2d641d848e6dd01e2eeda87c315f','Str. Garii 12');
INSERT INTO "Orders" ("id","clientId","productId","quantity","price") VALUES (1,1,1,3,6.0),
 (2,1,1,1,2.0),
 (3,1,1,3,6.0);
INSERT INTO "Products" ("id","name","price","quantity") VALUES (1,'Pepsi',2.0,2),
 (2,'Coca Cola',2.0,10),
 (3,'Fanta',2.5,10),
 (4,'Sprite',1.5,10),
 (5,'Schweppes',3.0,10);
INSERT INTO "logs" ("id","order_id") VALUES (1,1),
 (2,2),
 (3,3);
COMMIT;
