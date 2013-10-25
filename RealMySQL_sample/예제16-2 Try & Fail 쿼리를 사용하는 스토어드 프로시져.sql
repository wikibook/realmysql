DELIMITER ;;


CREATE PROCEDURE gettimelinearticle(
  IN in_memberid INT,                  /* 회원 번호 */
  IN in_base_dttm DATETIME,           /* 검색 기준 시간 - 이 시간 이전의 데이터부터 검색 */
  OUT out_articleids VARCHAR(2000))   /* 타임라인 게시물들의 번호를 리턴하는 출력 인자 */
BEGIN
  DECLARE v_fetched_count INT DEFAULT 0; /* 지금까지 읽은 게시물 건수 */
  DECLARE v_start_dttm DATETIME;         /* 검색 범위의 시작 일시 */
  DECLARE v_end_dttm DATETIME;          /* 검색 범위의 종료 일시 */
  DECLARE v_process_done BOOLEAN DEFAULT false; /* 타임라인 검색 작업의 완료 여부 */
  DECLARE v_hour_range INT DEFAULT 1;   /* 검색 범위의 시간 차이 */
  DECLARE v_base_dttm DATETIME;       /* 검색 기준 시간 */
  SET group_concat_max_len=1024*32;     /* GROUP_CONCAT 함수의 버퍼 크기를 32KB 로 조정 */

  IF ISNULL(in_base_dttm) THEN /* 검색 기준 시간이 주어지지 않으면 처음부터 조회 */
    SET v_base_dttm=NOW();
  ELSE                        /* 검색 기준 시간이 주어지면 그 시간부터 검색 */
    SET v_base_dttm=in_base_dttm;
  END IF;

  SET out_articleids='';          /* 프로시져 출력 인자의 값 초기화 */
  SET @_q_fetched_count=0;    /* Try & Fail 쿼리로 가져온 게시물 건수를 저장할 세션 변수 */
  SET @_q_articleid_buffer='';    /* Try & Fail 쿼리로 가져온 게시물 번호를 저장할 세션 변수 */
  SET @_q_memberid=in_memberid;  /* Try & Fail 쿼리의 변수 (회원 번호) */
  SET @_q_record_per_page=5;      /* 타임라인에서 한 페이지당 필요한 레코드 건수 */
  /* 쿼리를 프리페어 스테이트먼트 방식으로 실행하기 위해서 쿼리 문자열 조립 */
  SET @query=concat("SELECT COUNT(*), GROUP_CONCAT(article_id) INTO @_q_fetched_count, @_q_articleid_buffer ",
                    "FROM (SELECT ta.article_id ",
                    "      FROM tb_friend tf ",
                    "        INNER JOIN tb_article ta ON ta.write_memberid=tf.friend_member_id ",
                    "          AND ta.write_dttm>? ",  /* v_start_dttm */
                    "          AND ta.write_dttm<=? ", /* v_end_dttm */
                    "      WHERE tf.member_id=? ",     /* in_memberid */
                    "      ORDER BY ta.write_dttm DESC ",
                    "      LIMIT ? ) tb_derrived ");   /* LIMIT n, record_per_page */

  prepare v_stmt FROM @query; /* 프리페어 스테이트먼트 준비 */

  /* 미리 선정된 검색용 시간 범위를 재 설정 */
  WHILE v_process_done=FALSE DO
    IF v_hour_range<12 THEN
      SET v_hour_range=12;
    ELSEIF v_hour_range<24 THEN    /* 1 day */
      SET v_hour_range=24;
    ELSEIF v_hour_range<24*2 THEN  /* 2 day */
      SET v_hour_range=24*2;
    ELSEIF v_hour_range<24*4 THEN  /* 4 day */
      SET v_hour_range=24*4;
    ELSEIF v_hour_range<24*8 THEN  /* 8 day */
      SET v_hour_range=24*8;
    ELSEIF v_hour_range>=24*8 THEN /* All range */
      SET v_hour_range=0;          /* 0 ==> 전체 기간을 의미하는 상수로 사용됨 */
    END IF;

    /* 각 반복 회차 별로 검색 범위의 시작일시와 종료일시 재 설정 */
    SET v_end_dttm=v_base_dttm;
    SET v_start_dttm=DATE_SUB(v_base_dttm, INTERVAL v_hour_range HOUR);
    IF v_hour_range=0 THEN /* 만약 검색 범위 시간이 0이면 모든 레코드를 검색 */
      /* 현재 서비스 시작 일시(2011년 01월 01일)를 가장 오래된 게시물 작성 일시로 간주 */
      SET v_start_dttm='2011-01-01 00:00:00'; 
    END IF;

    SET @_q_start_dttm=v_start_dttm;  /*프리페어 스테이트먼트용 바인드 변수 준비 */
    SET @_q_end_dttm=v_end_dttm;   /*프리페어 스테이트먼트용 바인드 변수 준비 */

    /* 프리페어 스테이트먼트와 바인드 변수를 이용해서 쿼리 실행 */
    EXECUTE v_stmt USING @_q_start_dttm, @_q_end_dttm, @_q_memberid, @_q_record_per_page;
    SET v_fetched_count=v_fetched_count + @_q_fetched_count; /* 가져온 게시물 건수 누적 */

    IF @_q_fetched_count>0 THEN /* 가져온 게시물 번호가 있으면 출력 변수에 값 저장 */
      SET out_articleids=concat(out_articleids, ',', @_q_articleid_buffer);
    END IF;

    /* 한 페이지에서 필요한 레코드 건수만큼 조회가 되었거나, 더이상 검색할 시간 범위가 없으면 */
    IF (v_fetched_count>=@_q_record_per_page) OR (v_hour_range=0) THEN
      /* 더 이상 검색 대상이 없거나, 필요한 만큼의 레코드를 읽었다면 처리를 끝낸다 */
      SET v_process_done=true; 
    END IF;
    /* 계속해서 다음 검색 범위를 실행해야 하는 경우를 위해서 검색 기준 일시 재 설정 */
    SET v_base_dttm=v_start_dttm;
  END WHILE;

  deallocate prepare v_stmt;  /* 프리페어 스테이트먼트를 해제 */
END;;


DELIMITER ;