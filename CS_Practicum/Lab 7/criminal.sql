CREATE TABLE Face(
    id int NOT NULL,
    path_of_file varchar(255),
    h decimal,
    w decimal,
    x decimal,
    y decimal,
    PRIMARY KEY (id)
);

CREATE TABLE Criminal(
    id int NOT NULL,
    state boolean,
    PRIMARY KEY(id),
    FOREIGN KEY (id) references Face(id)
);

CREATE TABLE Junk_log(
    id int NOT NULL,
    path_of_file varchar(255),
    h decimal,
    w decimal,
    x decimal,
    y decimal,
    PRIMARY KEY(id)
);

CREATE TABLE Criminal_log(
    id int NOT NULL,
    path_of_file varchar(255),
    h decimal,
    w decimal,
    x decimal,
    y decimal,
    PRIMARY KEY(id)
);

CREATE TABLE Non_Criminal_log(
    id int NOT NULL,
    path_of_file varchar(255),
    h decimal,
    w decimal,
    x decimal,
    y decimal,
    PRIMARY KEY(id)
);