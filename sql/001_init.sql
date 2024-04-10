
CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE IF NOT EXISTS PhoneBook (
    id varchar (256) PRIMARY KEY,
    phone varchar (256) NOT NULL,
    name varchar (256) NOT NULL,
    address varchar (256) NOT NULL,
    
);

INSERT INTO AppUser
(id, username, email, password, role) VALUES (uuid_generate_v4(), '+375291091703', 'Андрей', 'Г.Минск');
