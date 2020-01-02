<?php
function fellowship_testimonials_add_all() {
        $page_content = "";
        $fellowship_testimonials_add_form = drupal_get_form("fellowship_testimonials_add_form");
        $page_content .= drupal_render($fellowship_testimonials_add_form);
        return $page_content;
    }
function fellowship_testimonials_add_form($form,$form_state, $testimonial_id = 0) {
         $testimonial_id = arg(2);
         $query = db_select('fellowship_testimonials');
         $query->fields('fellowship_testimonials');
         $query->condition('id', $testimonial_id);
         $result = $query->execute();
         $row = $result->fetchObject();
        $form = array();
        $form["fellowship_year"] = array(
            "#type" => "textfield",
            "#title" => "Enter the fellowship year participated by the fellow(s)",
            '#attributes' => array(
				'placeholder' => t('For eg: 2019')
			),
            "#default_value" => $row->year,
            "#required" => TRUE
        );
        $form["fellowship_task"] = array(
            "#type" => "textfield",
            "#title" => "Enter the fellowship task done by the fellow(s)",
            '#attributes' => array(
				'placeholder' => t('For eg: Python, DWSIM, eSim etc')
			),
            "#default_value" => $row->fellowship_task,
            "#required" => TRUE
        );

        $form["testimonial_video"] = array(
            "#type" => "textfield",
            "#title" => "Testimonial Video",
            '#attributes' => array(
				'placeholder' => t('Copy paste the static url of the video, for eg: https://static.fossee.in/fossee/videos/FOSSEE_intern_Video/DSC_0006.m4v')
			),
            "#default_value" => $row->testimonial_video,
            '#size' => 90,
            "#required" => TRUE
        );
        /*$form['fellows_fieldset'] = array(
            '#type' => 'fieldset',
            '#tree' => TRUE,
            '#prefix' => '<div id="fellows-fieldset-wrapper">',
            '#suffix' => '</div>'
        );
        if (empty($form_state['num_fellows'])) {
            $form_state['num_fellows'] = 1;
        }
        $temp = 0;
        for ($i = 0; $i < $form_state['num_fellows']; $i++) {
            $temp1 = $i;
            $form['fellows_fieldset'][$i]["s_text"] = array(
                "#type" => "item",
                "#markup" => "<h4><label>fellow : " . ($temp1 + 1) . "</label></h4>"
            );
            $form['fellows_fieldset'][$i]["fellowname"] = array(
                "#type" => "textfield",
                "#title" => "Name: ",
                "#default_value" => ""
            );
            $form['fellows_fieldset'][$i]["institute"] = array(
                "#type" => "textfield",
                "#title" => "Institute: ",
                "#default_value" => ""
            );
            $form['fellows_fieldset'][$i]["place"] = array(
                "#type" => "textfield",
                "#title" => "Place: ",
                "#default_value" => ""
            );
        }
        $form["fellows_count"] = array(
            "#type" => "hidden",
            "#value" => $temp1
        );
        $form['fellows_fieldset']['add_fellows'] = array(
            '#type' => 'submit',
            '#value' => t('Add fellow'),
            '#limit_validation_errors' => array(),
            '#submit' => array(
                'fellows_add_more_add_one'
            ),
            '#ajax' => array(
                'callback' => 'fellows_add_more_callback',
                'wrapper' => 'fellows-fieldset-wrapper'
            )
        );
        if ($form_state['num_fellows'] > 1) {
            $form['fellows_fieldset']['remove_fellows'] = array(
                '#type' => 'submit',
                '#value' => t('Remove Fellow'),
                '#limit_validation_errors' => array(),
                '#submit' => array(
                    'fellows_add_more_remove_one'
                ),
                '#ajax' => array(
                    'callback' => 'fellows_add_more_callback',
                    'wrapper' => 'fellows-fieldset-wrapper'
                )
            );
        }
        if ($no_js_use) {
            if (!empty($form['fellows_fieldset']['remove_fellows']['#ajax'])) {
                unset($form['fellows_fieldset']['remove_fellows']['#ajax']);
            }
            unset($form['fellows_fieldset']['add_fellows']['#ajax']);
        }*/
        $query_s = db_select('fellows');
        $query_s->fields('fellows');
        $query_s->condition('t_id', $row->id);
        $result_s = $query_s->execute();
        $num_of_fellowresults = $result_s->rowCount();

  $form['fellows_fieldset'] = array(
            '#type' => 'fieldset',
            '#tree' => TRUE,
            '#prefix' => '<div id="fellows-fieldset-wrapper">',
            '#suffix' => '</div>'
        );

    if ($num_of_fellowresults != 0) {

            $form_state['num_fellows'] = $num_of_fellowresults;
            $temp = 0;
            $i = 0;
            while ($row_s = $result_s->fetchObject()) {
                $temp = $i;
                $form['fellows_fieldset'][$i]["s_text"] = array(
                    "#type" => "item",
                    "#markup" => "<h4><label>fellows : " . ($temp + 1) . "</label></h4>"
                );
                $form['fellows_fieldset'][$i]["s_id"] = array(
                    "#type" => "hidden",
                    "#default_value" => $row_s->s_id
                );
                $form['fellows_fieldset'][$i]["fellowname"] = array(
                    "#type" => "textfield",
                    "#title" => "Name",
                    "#default_value" => $row_s->name
                );
                $form['fellows_fieldset'][$i]["institute"] = array(
                    "#type" => "textfield",
                    "#title" => "Institute",
                    "#default_value" => $row_s->institute
                );
                $form['fellows_fieldset'][$i]["place"] = array(
                    "#type" => "textfield",
                    "#title" => "Place",
                    "#default_value" => $row_s->place
                );
                
                $i++;
            }


            $form["fellows_count"] = array(
                "#type" => "hidden",
                "#value" => $temp
            );

        } 
        else {
            if (empty($form_state['num_fellows'])) {
                $form_state['num_fellows'] = 1;
            }
            $temp = 0;
            for ($i = 0; $i < $form_state['num_fellows']; $i++) {
                $temp = $i;
                $form['fellows_fieldset'][$i]["s_text"] = array(
                    "#type" => "item",
                    "#markup" => "<h4><label>fellows : " . ($temp + 1) . "</label></h4>"
                );
                $form['fellows_fieldset'][$i]["fellowname"] = array(
                    "#type" => "textfield",
                    "#title" => "Name",
                    "#default_value" => ""
                );
                $form['fellows_fieldset'][$i]["institute"] = array(
                    "#type" => "textfield",
                    "#title" => "University",
                    "#default_value" => ""
                );
                $form['fellows_fieldset'][$i]["place"] = array(
                    "#type" => "textfield",
                    "#title" => "Place",
                    "#default_value" => ""
                );
               
            }
            $form["fellows_count"] = array(
                "#type" => "hidden",
                "#value" => $temp
            );
            $form['fellows_fieldset']['add_fellows'] = array(
                '#type' => 'submit',
                '#value' => t('Add fellow'),
                '#limit_validation_errors' => array(),
                '#submit' => array(
                    'fellows_add_more_add_one'
                ),
                '#ajax' => array(
                    'callback' => 'fellows_add_more_callback',
                    'wrapper' => 'fellows-fieldset-wrapper'
                )
            );
            if ($form_state['num_fellows'] > 1) {
                $form['fellows_fieldset']['remove_fellows'] = array(
                    '#type' => 'submit',
                    '#value' => t('Remove'),
                    '#limit_validation_errors' => array(),
                    '#submit' => array(
                        'fellows_add_more_remove_one'
                    ),
                    '#ajax' => array(
                        'callback' => 'fellows_add_more_callback',
                        'wrapper' => 'fellows-fieldset-wrapper'
                    )
                );
            }
            if ($no_js_use) {
                if (!empty($form['fellows_fieldset']['remove_fellows']['#ajax'])) {
                    unset($form['fellows_fieldset']['remove_fellows']['#ajax']);
                }
                unset($form['fellows_fieldset']['add_fellows']['#ajax']);
            }
        }

        $form["testimonial_id"] = array(
            "#type" => "hidden",
            "#value" => $testimonial_id
        );
        $form["submit"] = array(
            "#type" => "submit",
            "#value" => "Submit"
        );
        return $form;
    }

    function fellows_add_more_callback($form, $form_state) {
    return $form['fellows_fieldset'];
}


function fellows_add_more_add_one($form, &$form_state) {
    $form_state['num_fellows']++;
    $form_state['rebuild'] = TRUE;
    //$form_state['no_redirect'] = TRUE;
}


function fellows_add_more_remove_one($form, &$form_state) {
    if ($form_state['num_fellows'] > 1) {
        $form_state['num_fellows']--;
    }
    $form_state['rebuild'] = TRUE;
}

    function fellowship_testimonials_add_form_validate($form, &$form_state) {
        // for future use
    }

    function fellowship_testimonials_add_form_submit($form, &$form_state) {
        $v = $form_state["values"];
        if($v["testimonial_id"]) {
            /*$query = "
                UPDATE fellowship_testimonials SET
                name = '%s', department = '%s', university = '%s',
                contribution = '%s', reference = '%s', body = '%s'
                WHERE id = %d
            ";
            $result = db_query($query, 
                $v["name"], $v["department"], $v["university"],
                $v["contribution"], $v["reference"], $v["body"],
                $v["testimonial_id"]
            );*/
            
            $query = db_update('fellowship_testimonials');
            $query->fields(array(
                'year' => $v["fellowship_year"],
                'fellowship_task' => $v["fellowship_task"],
                'testimonial_video' => $v["testimonial_video"]
            ));
            $query->condition('id', $v["testimonial_id"]);
            $result = $query->execute();
        } else {
            /*$query = "
                INSERT INTO fellowship_testimonials
                (name, department, university, contribution, reference, body)
                VALUES
                ('%s', '%s', '%s', '%s', '%s', '%s')
                ";
            $result = db_query($query, 
                $v["name"], $v["department"], $v["university"],
                $v["contribution"], $v["reference"], $v["body"]
            );*/
            
            $query = "
                INSERT INTO fellowship_testimonials
                (year, fellowship_task, testimonial_video)
                VALUES
                (:year, :fellowship_task, :testimonial_video)
                ";
            $args = array( 
                ':year' => $v["fellowship_year"],
                ':fellowship_task' => $v["fellowship_task"],
                ':testimonial_video' => $v["testimonial_video"]
                );
                
            $result = db_query($query,$args, array(
        'return' => Database::RETURN_INSERT_ID
    ));
        
        //var_dump($result->name);die;
        $fellowsupload = 0;
        for ($i = 0; $i <= $v["fellows_count"]; $i++) {
           $s_id=$v['fellows_fieldset'][$i]["f_id"];
            if ($s_id != "") {
                if ($v['fellows_fieldset'][$i]["fellowname"] != "") {
                    $query = db_update('fellows');
                    $query->fields(array(
                        'name' => $v['fellows_fieldset'][$i]["fellowname"],
                        'institute' => $v['fellows_fieldset'][$i]["institute"],
                        'place' => $v['fellows_fieldset'][$i]["place"]
                    ));
                    $query->condition('f_id', $v['fellows_fieldset'][$i]["s_id"]);
                    $result = $query->execute();
                    if ($result != 0) {
                        $fellowsupload++;
                    }
                }
            } 
             else {
                if ($v['fellows_fieldset'][$i]["fellowname"] != "") {
                    $fellowsquery = "
  INSERT INTO fellows
  (t_id,name,institute,place)
  VALUES
  (:t_id,:name,:institute,:place)
  ";
                    $fellowsargs = array(
                        ":t_id" => $result,
                        ":name" => $v['fellows_fieldset'][$i]["fellowname"],
                        ":institute" => $v['fellows_fieldset'][$i]["institute"],
                        ":place" => $v['fellows_fieldset'][$i]["place"]
                    );
                    /* storing the row id in $result */
                    $fellowsresult = db_query($fellowsquery, $fellowsargs, array(
                        'return' => Database::RETURN_INSERT_ID
                    ));
                    if ($fellowsresult != 0) {
                        $fellowsupload++;
                    }
                }
            }
        }
    }
        if(!$result) {
            drupal_set_message("Something went wrong, please try again.", "error");
        } else {
            drupal_set_message("Testimonial added successfully", "status");
        }
    }

function fellowship_testimonials_edit_all($testimonial_id=0) {
      
        $page_content = "";
        
        if($testimonial_id){
              
              $fellowship_testimonials_add_form = drupal_get_form("fellowship_testimonials_add_form", $testimonial_id);
              $page_content .= drupal_render($fellowship_testimonials_add_form);
        } else {
            /*$query = "
                SELECT * FROM fellowship_testimonials
                ORDER BY time DESC
                ";
            $result = db_query($query);*/
             $speakerquery = db_select('fellows');
            $speakerquery->fields('fellows');
            
            $speakerresult = $speakerquery->execute();
            while($speakerrow = $speakerresult->fetchObject()){
            $query = db_select('fellowship_testimonials');
            $query->fields('fellowship_testimonials');
           // $query->orderBy('time', 'DESC');
            $query->condition('id', $speakerrow->t_id);
            $result = $query->execute();

                        $headers = array(
                "Name", "University", "Action"
            );
            $rows = array();
            while($row = $result->fetchObject()) {
                $item = array(
                    $speakerrow->name,
                    $speakerrow->institute,
                    l("Edit", "fellowship_testimonials/edit/{$row->id}") ." | ".
                    l("Delete", "fellowship_testimonials/delete/{$row->id}")
                );
                array_push($rows, $item);
            }
        }
            //$page_content .= theme("table", $headers, $rows);
            $page_content .= theme('table', array('header' => $headers, 'rows' => $rows ));
        }
        return $page_content;
    }
