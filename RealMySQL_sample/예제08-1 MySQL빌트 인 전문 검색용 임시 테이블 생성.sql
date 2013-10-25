CREATE TABLE ft_article (
  doc_id INT NOT NULL,
  doc_title VARCHAR(1000) NOT NULL,
  doc_body TEXT,
  PRIMARY KEY (doc_id),
  FULLTEXT KEY fx_article (doc_title,doc_body)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO ft_article VALUES
(1, 'it is possible', 'it is possible to subpartition tables that are partitioned by RANGE or LIST'),
(2, 'Subpartitions may', 'Subpartitions may use either HASH or KEY partitioning'),
(3, 'This is also', 'This is also known as composite partitioning'),
(4, 'SUBPARTITION BY HASH', 'SUBPARTITION BY HASH and SUBPARTITION BY KEY generally follow the same syntax rules'),
(5, 'An exception', 'An exception to this is that SUBPARTITION BY KEY (unlike PARTITION BY KEY)');

