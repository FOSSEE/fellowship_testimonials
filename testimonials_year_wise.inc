<?php
function fellowship_testimonials_display_year_wise() {
        $page_content = "";
        /*$query = "
            SELECT * FROM fellowship_testimonials
            ORDER BY id DESC
        ";
        $result = pager_query($query, 4, 0, "SELECT COUNT(*) FROM fellowship_testimonials");*/
         $query = db_select('fellowship_testimonials');
         $query->fields('fellowship_testimonials');
         $query->orderBy('year', $year);
         $result = $query->extend('PagerDefault')->limit(3)->execute();
        
        $page_content .= "<div id='fellowship_testimonials-wrapper'>";
        while($row = $result->fetchObject()) {
            $speakerquery = db_select('fellows');
            $speakerquery->fields('fellows');
            $speakerquery->condition('t_id', $row->id);
            $speakerresult = $speakerquery->execute();
           
            $page_content .= "
              <div class='container-testimonial'>
 <video title='' controls='' preload='' data-setup='{}' width='500' height='400'>
 <source src={$row->testimonial_video} type='video/mp4'>
                                </video> ";
 while($speakerrow = $speakerresult->fetchObject()){
        $page_content .= "<p><span>{$speakerrow->name}</span><br>Institute: {$speakerrow->institute}, {$speakerrow->place}<br><br><span style='margin-right:0;'>";
    }
            $page_content .= "Fellowship task</span>: {$row->fellowship_task}
            <br><br><span>Fellowship Year</span>: {$row->year}</p></div>";
            
    }
        $page_content .= "</div> <!-- /#fellowship_testimonials-wrapper -->";
        //$page_content .= theme("pager", NULL, 4, 0);
        $page_content .= theme('pager', array('header' => NULL, 'rows' => 4 ));
        return $page_content;
    }