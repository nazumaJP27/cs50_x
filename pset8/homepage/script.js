document.addEventListener('DOMContentLoaded', function()
{
    // Contents of .navbar-top
    const navbar_top = document.querySelector('.navbar-top');
    if (navbar_top)
    {
        navbar_top.innerHTML = `
            <button class="nav-toggle"><i class="bi bi-list"></i></button>
            <ul>
                <li><a href="index.html">Home</a></li>
                <li><a href="projects.html">Projects</a></li>
                <li><a href="cv.html">CV</a></li>
                <li><a href="hobbies.html">Hobbies</a></li>
            </ul>
        `;
    }

    // Contents of .page-footer
    const page_footer = document.querySelector('.page-footer');
    if (page_footer)
    {
        page_footer.innerHTML = `
            <hr class="footer-hr">
            <p>
                <i class="bi bi-envelope-fill"> Email me at: <a href="mailto:jpseibt@gmail.com">jpseibt@gmail.com</a></i>
            </p>
            <p>
                <i class="bi bi-linkedin">
                    I'm on LinkedIn:
                    <a
                        href="https://www.linkedin.com/in/jpaulo-seibt"
                        target="_blank"
                    >
                        linkedin.com/in/jpaulo-seibt
                    </a>
                </i>
            </p>
            <p>
                <i class="bi bi-github">
                    My GitHub:
                    <a
                        href="https://github.com/nazumaJP27"
                        target="_blank"
                    >
                        github.com/nazumaJP27
                    </a>
                </i>
            </p>
            <p><a href="#">Go to top.</a></p>
        `;
    }

    // Set the navigation menu toggle (only on mobile)
    if (window.matchMedia("(max-width: 580px)").matches) {
        const nav_toggle = document.querySelector('.nav-toggle');
        nav_toggle.addEventListener('click', function()
        {
            nav_toggle.classList.toggle('active');
            nav_toggle.parentElement.querySelector('ul').classList.toggle('show');
        });
    }

    // Set the active navigation tab for the current page
    const tab_indexes = {
        "Home": 0,
        "Projects": 1,
        "CV": 2,
        "Hobbies": 3
    };

    let active_tab_index = tab_indexes[document.title.split(" - ").pop()];
    console.log("Active Tab:", active_tab_index);

    // Give active-tab class to the corresponding tab
    let nav_tabs = document.querySelectorAll('.navbar-top > ul > li');
    nav_tabs[active_tab_index].classList.add('active-tab');

    for (let i = 0; i < nav_tabs.length; i++)
    {
        nav_tabs[i].addEventListener('click', function()
        {
            if (active_tab_index != i)
            {
                nav_tabs[i].classList.add('active-tab');
                // remove active-tab class from previous tab index
                nav_tabs[active_tab_index].classList.remove('active-tab');
                active_tab_index = i;
                nav_tabs[i].firstChild.click(); // Go to anchor href
            }
        });
    }
});