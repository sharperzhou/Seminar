// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

$(document).ready(()=>{
    $('.done-checkbox').on('click', e=>{
        let checkbox = e.target;
        checkbox.disable = true;

        let row = checkbox.closest('tr');
        $(row).addClass('done');

        let form = checkbox.closest('form');
        form.submit();
    });
});