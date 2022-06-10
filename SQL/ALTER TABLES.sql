-- This needs to be done after creating the tables because of other FOREIGN KEY REFERENCES
ALTER TABLE Component add CONSTRAINT FK_COBPID FOREIGN KEY (COBPID) REFERENCES Blueprint (BPID)
ALTER TABLE T1Product add CONSTRAINT FK_T1BPID FOREIGN KEY (T1BPID) REFERENCES Blueprint (BPID)
ALTER TABLE T2Product add CONSTRAINT FK_T2BPID FOREIGN KEY (T2BPID) REFERENCES Blueprint (BPID)
ALTER TABLE T3Product add CONSTRAINT FK_T3BPID FOREIGN KEY (T3BPID) REFERENCES Blueprint (BPID)

-- Columns to Add
ALTER TABLE Blueprint ADD BPGroup NVARCHAR(50) NOT NULL

-- Change NVARCHAR from 50 to 100 because of longer Item Names
ALTER TABLE Blueprint    ALTER COLUMN BPName NVARCHAR(100)
ALTER TABLE Blueprint    ALTER COLUMN BPProduct NVARCHAR(100)

ALTER TABLE T1Product    ALTER COLUMN T1Name NVARCHAR(100)
ALTER TABLE T1Product    ALTER COLUMN T1Group NVARCHAR(100)

--To bring Formulas also into Blueprint Table a Type Column is added
--The different Blueprints get a string declaring if they are T1/T2/T3 or Formulas
-- As in this particular moment there are onyl T1 Products in the table this is set as a default value

ALTER TABLE Blueprint ADD BPType NVARCHAR(20) NOT NULL DEFAULT 'T1Product'


