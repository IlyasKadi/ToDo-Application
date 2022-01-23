<div id="top"></div>


<!-- PROJECT LOGO -->
<br />
<div align="center">
    <img src="images/logo.png" alt="Logo" width="550" height="380">
  <h2 align="center">📝ToDo Application using containers</h2>
  <h3 align="center">Create a versatile Todo app using (Item/Model) based containers.</h3>
</div>


<!-- TABLE OF CONTENTS -->

  <summary>Table of Contents</summary>
  <ol>      
      <a href="#about-the-project">About The Project</a>         
      <li><a href="#Overview">Overview</a></li>
      <li><a href="#Use-Cases">Use Cases</a></li> 
      <li><a href="#Defining-a-Task">Defining a Task</a></li> 
      <li><a href="#Item-Based-Model">Item Based Model</a></li> 
      <li><a href="#MVC-Model">MVC Model</a></li>
  </ol>



<!-- ABOUT THE PROJECT -->
# About The Project

<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

1. [**How to install Qt**](https://anassbelcaid.github.io/CS221/qtcreator/)
2. **Clone the repo**
   ```sh
   git clone https://github.com/IlyasKadi/ToDo-Application.git
   ```
 
<p align="right">(<a href="#top">back to top</a>)</p>


📝📧📆🗑️❗⚠️

<!-- Overview -->
# Overview  📝


<div align="center">
    <img src="images/inter.png"/>
</div>

> Overview of our application. 


<div align="center">
    <img src="images/todoApp.gif"alt="animation" width="100" height="100"/>
</div>

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Use-Cases -->
# Use-Cases

Here is a list of **cases** that the user could **perform** with our app:

   1. A user should be able to **close** the application of course.
   2. A Todo application cannot be useful, unless it offers the possibility of **creating new tasks**.    
   3. The View of the main widget should be **split** in **three** areas:   
        1. The first (en persistent) area shows the list of **today** tasks.
        2. The second one is reserved for **pending** task (tasks for the future).
        3. Finally, the third one shows the set of **finished** tasks.
        
   4. Each category must be shown with a **custom** icon.

   5. The user could either `hide/show` the pending and finished views.

   6. Finally, the tasks entered to your application must remains in the app in future use.

   > Meaning, If I create a task and I close the application, next time I opened the application, I should find my tasks and not start from scratch.







<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Defining-a-Task -->
# Defining-a-Task

A `Task` is defined by the following attributes:

   - A `description`: stating the text and goal for the task like (Buying the milk).
   - A `finished` boolean indicating if the task is Finished or due.
   - A `Tag` category to show the class of the task which is reduced to the following values:
       - Work
       - Life
       - Other
   - Finally, a task should have a `DueDate` which stores the **Date** planned for the date.

When the user create a new task, the application must **pop up** a dialog for the user to get those values. Here is an example ( not mandatory, I prefer you create your own) example:



<div align="center">
    <img src="images/dialog.png"/>
</div>

> An example of a dialog to get a new task.

<p align="right">(<a href="#top">back to top</a>)</p>



<!-- Item-Based-Model -->
# Item-Based-Model




<p align="right">(<a href="#top">back to top</a>)</p>


<!-- MVC-Model -->
# MVC-Model




<p align="right">(<a href="#top">back to top</a>)</p>


 
-------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Our Team     : [AIT EL KADI Ilyas](https://github.com/IlyasKadi) - [AZIZ Oussama](https://github.com/ATAMAN0)  
 
   Project Link : [ToDo-Application](https://github.com/IlyasKadi/ToDo-Application)   
 
  > Encadré par  : [Mr.BELCAID-Anass](https://anassbelcaid.github.io)  
                                                                                             
<p align="right">(<a href="#top">back to top</a>)</p>
