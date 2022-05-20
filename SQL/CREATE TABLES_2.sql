CREATE TABLE Salvage
(
    SALID int PRIMARY KEY IDENTITY(1,1),
    SALName NVARCHAR(50) NOT NULL,
    SALSize FLOAT NOT NULL,
	SALGroup NVARCHAR(50) NOT NULL,
	SALImage 		NVARCHAR(256) 	NULL,
	SALImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE MoonGoo
(
    MGID int PRIMARY KEY IDENTITY(1,1),
    MGName NVARCHAR(50) NOT NULL,
    MGSize FLOAT NOT NULL,
	MGGroup NVARCHAR(50) NOT NULL,
	MGImage 		NVARCHAR(256) 	NULL,
	MGImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE T1Product
(
    T1ID int PRIMARY KEY IDENTITY(1,1),
    T1Name NVARCHAR(50) NOT NULL,
    T1Size FLOAT NOT NULL,
	T1Group NVARCHAR(50) NOT NULL,
	T1Blueprint int NULL,
	T1Image 		NVARCHAR(256) 	NULL,
	T1ImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE T2Product
(
    T2ID int PRIMARY KEY IDENTITY(1,1),
    T2Name NVARCHAR(50) NOT NULL,
    T2Size FLOAT NOT NULL,
	T2Group NVARCHAR(50) NOT NULL,
	T2Blueprint int NULL,
	T2Image 		NVARCHAR(256) 	NULL,
	T2ImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE T3Product
(
    T3ID int PRIMARY KEY IDENTITY(1,1),
    T3Name NVARCHAR(50) NOT NULL,
    T3Size FLOAT NOT NULL,
	T3Group NVARCHAR(50) NOT NULL,
	T3Blueprint int NULL,
	T3Image 		NVARCHAR(256) 	NULL,
	T3ImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE Gas
(
    GID int PRIMARY KEY IDENTITY(1,1),
    GName NVARCHAR(50) NOT NULL,
    GSize FLOAT NOT NULL,
	GGroup NVARCHAR(50) NOT NULL,
	GImage 		NVARCHAR(256) 	NULL,
	GImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE FactionMaterial
(
    FMID int PRIMARY KEY IDENTITY(1,1),
    FMame NVARCHAR(50) NOT NULL,
    FMSize FLOAT NOT NULL,
	FMGroup NVARCHAR(50) NOT NULL,
	FMImage 		NVARCHAR(256) 	NULL,
	FMImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE NamedComponent
(
    NCID int PRIMARY KEY IDENTITY(1,1),
    NCName NVARCHAR(50) NOT NULL,
    NCSize FLOAT NOT NULL,
	NCGroup NVARCHAR(50) NOT NULL,
	NCImage 		NVARCHAR(256) 	NULL,
	ImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE IceProduct
(
    ICEID int PRIMARY KEY IDENTITY(1,1),
    ICEName NVARCHAR(50) NOT NULL,
    ICESize FLOAT NOT NULL,
	ICEGroup NVARCHAR(50) NOT NULL,
	ICEImage 		NVARCHAR(256) 	NULL,
	ICEImageFile 	VARBINARY(MAX) 	NULL
);