CREATE Database EVE_Manufacture_Planner
Go
USE EVE_Manufacture_Planner

CREATE TABLE Source
(
    SOID    int PRIMARY KEY IDENTITY(1,1),
    SOName  NVARCHAR(50) NOT NULL,
    SODensity int NOT NULL,      
);

CREATE TABLE Planet
(
    PLID 			int 			PRIMARY key IDENTITY (1,1),
    PLName 			NVARCHAR(36) 	NOT NULL,
    PLSystemname 	Nvarchar(30) 	NOT NULL,
    PLType 			nvarchar(30) 	NOT NULL,
    PLSource_1 		int 			NULL,
    PLSource_2 		int 			NULL,
    PLSource_3 		int 			NULL,
    PLSource_4 		int 			NULL,
    PLSource_5 		int 			NULL,
	PLImage 		NVARCHAR(256) 	NULL,
	PLImageFile 	VARBINARY(MAX) 	NULL,
	
    FOREIGN KEY (PLSource_1) REFERENCES Source (SOID),
    FOREIGN KEY (PLSource_2) REFERENCES Source (SOID),
    FOREIGN KEY (PLSource_3) REFERENCES Source (SOID),
    FOREIGN KEY (PLSource_4) REFERENCES Source (SOID),
    FOREIGN KEY (PLSource_5) REFERENCES Source (SOID)
);

CREATE TABLE Mineral
(
    MINID 			int 			PRIMARY KEY IDENTITY(1,1),
    MINName 		NVARCHAR(50) 	NOT NULL,
    MINSize 		FLOAT 			NOT NULL,
	MINGroup 		NVARCHAR(50) 	NOT NULL,
	MINImage 		NVARCHAR(256) 	NULL,
	MINImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE Component
(
    COID 		int 			PRIMARY KEY IDENTITY(1,1),
    COName 		NVARCHAR(50) 	NOT NULL,
    COSize 		FLOAT 			NOT NULL,
	COGroup 	NVARCHAR(50) 	NOT NULL,
	COBPID		int 			NULL,
	COImage 	NVARCHAR(256) 	NULL,
	COImageFile VARBINARY(MAX) 	NULL
);

CREATE TABLE PIProduct			
(
    PIID int PRIMARY KEY IDENTITY(1,1),
    PIName	        	nvarchar(50)    NOT NULL,
    PISize	        	float           NOT NULL,
	PIGroup				nvarchar(50)	NOT NULL,
    PIIngredient_1		int	            NULL,
    PIIngredient_2		int	            NULL,
    PIIngredient_3		int	            NULL,
    PIPx	        	nvarchar(4)     NOT NULL,
    PIIngredientamount	int				NOT NULL,
    PIQuantity 			int	            NOT NULL,
	PIImage 			NVARCHAR(256) 	NULL,
	PIImageFile 		VARBINARY(MAX) 	NULL,
	--Selfreference to store 3 depending ingredients
    FOREIGN KEY (PIIngredient_1) REFERENCES PIProduct (PIID),
    FOREIGN KEY (PIIngredient_2) REFERENCES PIProduct (PIID),
    FOREIGN KEY (PIIngredient_3) REFERENCES PIProduct (PIID)
);


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
    T1ID 			int 			PRIMARY KEY IDENTITY(1,1),
    T1Name 			NVARCHAR(100) 	NOT NULL,
    T1Size 			FLOAT 			NOT NULL,
	T1Group 		NVARCHAR(100) 	NOT NULL,
	T1BPID 			int 			NULL,
	T1Image 		NVARCHAR(256) 	NULL,
	T1ImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE T2Product
(
    T2ID 			int PRIMARY KEY IDENTITY(1,1),
    T2Name 			NVARCHAR(50) NOT NULL,
    T2Size 			FLOAT NOT NULL,
	T2Group 		NVARCHAR(50) NOT NULL,
	T2BPID			int NULL,
	T2Image 		NVARCHAR(256) 	NULL,
	T2ImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE T3Product
(
    T3ID 			int PRIMARY KEY IDENTITY(1,1),
    T3Name 			NVARCHAR(50) NOT NULL,
    T3Size 			FLOAT NOT NULL,
	T3Group 		NVARCHAR(50) NOT NULL,
	T3BPID			int NULL,
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
    NCID 		int 			PRIMARY KEY IDENTITY(1,1),
    NCName 		NVARCHAR(50) 	NOT NULL,
    NCSize 		FLOAT 			NOT NULL,
	NCGroup 	NVARCHAR(50) 	NOT NULL,
	NCImage 	NVARCHAR(256) 	NULL,
	ImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE IceProduct
(
    ICEID 			int 			PRIMARY KEY IDENTITY(1,1),
    ICEName 		NVARCHAR(50) 	NOT NULL,
    ICESize 		FLOAT 			NOT NULL,
	ICEGroup 		NVARCHAR(50) 	NOT NULL,
	ICEImage 		NVARCHAR(256) 	NULL,
	ICEImageFile 	VARBINARY(MAX) 	NULL
);

CREATE TABLE Material
(			
    MATID	    int		PRIMARY KEY IDENTITY(1,1),
    MATPIID	    int		NULL,
    MATMINID	int		NULL,
    MATCOID	    int		NULL,
	
	MATSALID 	int 	NULL,
	MATMGID 	int 	NULL,
	MATT1ID 	int 	NULL,
	MATT2ID 	int 	NULL,
	MATT3ID 	int 	NULL,
	MATGID 		int 	NULL,
	MATFMID 	int 	NULL,
	MATNCID 	int 	NULL,
	MATICEID 	int 	NULL,
	
    FOREIGN KEY (MATPIID) REFERENCES PIProduct (PIID),
    FOREIGN KEY (MATMINID) REFERENCES Mineral (MINID),
    FOREIGN KEY (MATCOID) REFERENCES Component (COID),
	
	FOREIGN KEY (MATSALID) REFERENCES Salvage (SALID),
	FOREIGN KEY (MATMGID) REFERENCES MoonGoo (MGID),
	FOREIGN KEY (MATT1ID) REFERENCES T1Product (T1ID),
	FOREIGN KEY (MATT2ID) REFERENCES T2Product (T2ID),
	FOREIGN KEY (MATT3ID) REFERENCES T3Product (T3ID),
	FOREIGN KEY (MATGID) REFERENCES Gas (GID),
	FOREIGN KEY (MATFMID) REFERENCES FactionMaterial (FMID),
	FOREIGN KEY (MATNCID) REFERENCES NamedComponent (NCID),
	FOREIGN KEY (MATICEID) REFERENCES IceProduct (ICEID)
);

Go

CREATE TABLE Blueprint
(			
    BPID		int				PRIMARY KEY IDENTITY(1,1),
    BPName		nvarchar(50)	NOT NULL,
    BPProduct	text			NOT NULL,
    BPAmount	int				NOT NULL
)
Go
CREATE TABLE BlueprintMaterials
(
    BPMID	    int     	PRIMARY KEY IDENTITY(1,1),	
    BPMAmount   int         NOT NULL,
    BPMBPID	    int	    	NOT NULL,
    BPMMATID    int		 	NOT NULL,    
	
    FOREIGN KEY (BPMBPID) REFERENCES Blueprint (BPID),
    FOREIGN KEY (BPMMATID) REFERENCES Material (MATID)
)





